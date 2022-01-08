#include <stdexcept>
#include "gitapi.hpp"
#include "utility.hpp"

namespace gitgui {
	static const QString programm{"git"};
	
	// Recursive function for build commit tree
	void buildCommitTree(QList<QStringList> &commitTree, const QString &commit, sharedTreeCommitNode &currTreeCommitNode);

	GitApi::GitApi(const QString& workdir) 
	{
		setRootPathRepository(workdir);
	}
	
	Branch GitApi::getActiveBranch() {
		QStringList args;
		args << "rev-parse";
		args << "--symbolic-full-name";
		args << "--abbrev-ref";
		args << "HEAD";
		QString branchName{mProcess.run(programm, args)};
		branchName = branchName.mid(0, branchName.indexOf("\n"));
		QString branchSHA{mProcess.run(programm, QStringList() << "rev-parse" << branchName)};
		branchSHA = branchSHA.mid(0, branchSHA.indexOf("\n"));
		
		QTextStream(stdout) << "branche name: " << branchName << " sha: " << branchSHA << endl;
		
		return Branch{branchSHA, branchName};
	}
	
	Commit GitApi::getActiveCommit() {
		QStringList args;
		args << "rev-parse";
		args << "HEAD";
		QStringList actSHA{mProcess.run(programm, args).split('\n')};
		return Commit{QString{actSHA[0]}};
	}
	
	void GitApi::checkout(const SHA& sha) {
		QStringList args;
		args << "checkout";
		args << sha.sha();
		QTextStream(stdout) << "make checkout: " << sha.sha() << endl;
		// mProcess.run(programm, args);
	}
	
	void GitApi::setRootPathRepository(const QString &workdir) {
		if (workdir.isEmpty())
			mProcess.setWorkDirectory(QString("."));
		else
			mProcess.setWorkDirectory(workdir);
		mRootGitPath = mProcess.run(programm, QStringList() << "rev-parse" << "--show-toplevel");
		mRootGitPath = mRootGitPath.mid(0, mRootGitPath.indexOf("\n"));
		if (mRootGitPath.contains(QRegExp("^fatal")) || mRootGitPath.isEmpty()) {
			throw std::invalid_argument(("GitApi::GitApi(const QString&) => No git repo in path: " + workdir).toStdString());
		}
		mProcess.setWorkDirectory(mRootGitPath);
	}

	std::list<Branch> GitApi::branchList() {
		QStringList arg;
		arg << "branch";
		arg << "-v";
		arg << "--no-abbrev";
		arg << "--all";
		
		enum TypeBranchTitles {
			POINT_TO_BRANCH,
			SHA_BRANCH,
			NAME_BRANCH,
			END_TYPE
		};
		
		// Get list of branch
		QStringList listBranch{mProcess.run(programm, arg).split('\n')};
		if (listBranch.isEmpty())
			return std::list<Branch>{};
		
		// Split line to branch titles
		QList<QStringList> allBranches(gitutility::splitStringToListStringList(listBranch, QString(" ")));
		
		// Parse each branch line and save name and sha for create branch object
		std::list<Branch> branches;
		for (int i = 0; i < allBranches.size(); ++i) {
			TypeBranchTitles branchTytliType = TypeBranchTitles::POINT_TO_BRANCH;
			QString branchName, branchSha;
			for (int j = 0; j < allBranches[i].size(); ++j) {
				switch(branchTytliType) {
					case TypeBranchTitles::POINT_TO_BRANCH:
						if (allBranches[i][j] == "*")
							branchTytliType = TypeBranchTitles::NAME_BRANCH;
						else {
							branchName = allBranches[i][j];
							branchTytliType = TypeBranchTitles::SHA_BRANCH;
						}
						break;
					case TypeBranchTitles::NAME_BRANCH:
						branchName = allBranches[i][j];
						branchTytliType = TypeBranchTitles::SHA_BRANCH;
						break;
					case TypeBranchTitles::SHA_BRANCH:
						branchSha = allBranches[i][j];
						branchTytliType = TypeBranchTitles::END_TYPE;
						break;
				}
				if (branchTytliType == TypeBranchTitles::END_TYPE)
					break;
			}
			// Create branch and add to banch list
			branches.push_back(Branch{branchSha, branchName});
		}
		return branches;
	}
	
	QString GitApi::commitChanges(const SHA &sha) {
		if (sha.sha().isEmpty())
			return QString();
		QStringList args;
		args << "show";
		args << sha.sha();
		return mProcess.run(programm, args);
	}

	sharedTreeCommitNode GitApi::getRootCommitTree() {
		QStringList arguments;
		arguments << "rev-list";
		arguments << "--parents";
		arguments << "--all";

		// Read string commits
		QStringList listCommits = mProcess.run(programm, arguments).split('\n');
		if (listCommits.empty())
			return sharedTreeCommitNode{};
		QList<QStringList> splitCommits(gitutility::splitStringToListStringList(listCommits, QString(" ")));
		
		// Create branch with all commits
		sharedTreeCommitNode rootCommitNode{new TreeCommitNode(Commit(QString{}))};
		auto allCommits = rootCommitNode->addChild(Commit{allCommit});
		for (int i = 0; i < splitCommits.size(); ++i)
			allCommits->addChild(Commit{splitCommits[i][0]});
		
		// Create hierarchical branch of commits
		auto treeCommits = rootCommitNode->addChild(Commit{treeCommit});
		buildCommitTree(splitCommits, splitCommits[0][0], treeCommits);
		return rootCommitNode;
	}

	void buildCommitTree(QList<QStringList> &commitTree, const QString &commit, sharedTreeCommitNode &currTreeCommitNode) {
		for (int i = 0; i < commitTree.size(); ++i) {
			if (commitTree[i][0] == commit) {
				sharedTreeCommitNode branch = currTreeCommitNode->addChild(Commit{commitTree[i][0]});
				if (commitTree[i].size() > 1) {
					for(int j = 2; j < commitTree[i].size(); ++j) 
						buildCommitTree(commitTree, commitTree[i][j], branch);
					buildCommitTree(commitTree, commitTree[i][1], currTreeCommitNode);
				}
				break;
			}
		}
	}
	
}