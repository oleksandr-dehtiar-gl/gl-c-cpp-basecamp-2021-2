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
	
	bool GitApi::fatalErrorExist(const QString& gitApiOutString) {
		return gitApiOutString.contains(QRegExp("^fatal"));
	}

	QString GitApi::getPathFromURL(const QString& url) {
		return gitutility::getStringMatchRegex(QRegExp("([^/]+)(?=.git)"), url);
	}
	
	QString GitApi::findStarsActiveBranch(const QString& str) {
		return gitutility::getStringMatchRegex(QRegExp("(^\\*)"), str);
	}
	
	QString GitApi::findSHAFromString(const QString& str) {
		return gitutility::getStringMatchRegex(QRegExp("([\\d\\w]{40})"), str);
	}
	
	QString GitApi::findHEADdetachedBranch(const QString& str) {
		return gitutility::getStringMatchRegex(QRegExp("(\\(HEAD.*\\))"), str);
	}
	
	QString GitApi::findNameBranch(const QString& str) {
		return gitutility::getStringMatchRegex(QRegExp("(?![\\s+\\*])\\S+"), str);
	}
	
	// ........................................................
	QString GitApi::makeCommit(const QString& msg) {
		QStringList args;
		args << "commit";
		args << "-s";
		args << "-m";
		if (!msg.isEmpty())
			args << QString{"\"" + msg + "\""};
		return mProcess.run(programm, args);
	}
	
	void GitApi::removeFromIndexStage(const std::list<IndexFile> &fileList) {
		if (fileList.empty())
			return;
		QStringList files;
		files << "restore";
		files << "--staged";
		for (auto &file : fileList)
			files << file.name();
		mProcess.run(programm, files);
	}
	
	void GitApi::addToIndexStage(const std::list<IndexFile> &fileList) {
		if (fileList.empty())
			return;
		QStringList files;
		files << "add";
		for (auto &file : fileList) {
			files << file.name();
		}
		mProcess.run(programm, files);
	}
	
	std::list<IndexFile> GitApi::getIndexFilesList() {
		QStringList result{mProcess.run(programm, QStringList() << "status" << "-s").split("\n")};
		std::list<IndexFile> list;
		for (auto &line : result) {
			if (line.isEmpty())
				continue;
			if (line.size() <= 3)
				return list;
			IndexFile file{line.mid(3)};
			if (line[0] == " " || line[0] == "?")
				file.setNotIndexed();
			else
				file.setIndexed();
			list.push_back(std::move(file));
		}
		return list;
	}
	
	QString GitApi::cloneRepository(QString url, QString path) {
		if (url.isEmpty())
			return QString{};
		
		// If path empty get path from git url
		if (path.isEmpty()) {
			path = getPathFromURL(url);
			if (path.isEmpty())
				return QString{};
		}
		
		// Clone repo and check if repository exist in clone direcory "path"
		QDir dirRepo(path);
		Process(programm, QStringList() << "clone" << url << path).run();
		return dirRepo.exists() ? path = dirRepo.absolutePath() : QString{};
	}
	
	std::list<Commit> GitApi::getCommitsWhenTextChanged(const QString& text) {
		QStringList args;
		args << "log";
		args << "-S";
		args << text;
		args << "--source";
		args << "--all";
		QStringList resultCommits{mProcess.run(programm, args).split("\n")};
		std::list<Commit> listCommits;
		for(auto &line : resultCommits) {
			if (line.isEmpty())
				continue;
			if (line.contains(QRegExp("^\\s*commit")))
				listCommits.push_back(Commit{findSHAFromString(line)});
		}
		return std::move(listCommits);
	}
	
	Branch GitApi::getActiveBranch() {
		// Get working branch
		QString branchName{mProcess.run(programm, QStringList() << "branch" << "--show-current")};
		branchName = branchName.mid(0, branchName.indexOf("\n"));	
		QString branchSHA{mProcess.run(programm, QStringList() << "rev-parse" << branchName)};
		branchSHA = branchSHA.mid(0, branchSHA.indexOf("\n"));
		return Branch{branchSHA, branchName};
	}
	
	Commit GitApi::getActiveCommit() {
		// Define current working commit 
		QStringList args;
		args << "rev-parse";
		args << "HEAD";
		// QStringList actSHA{mProcess.run(programm, args).split('\n')};
		return Commit{findSHAFromString(mProcess.run(programm, args))};
	}
	
	void GitApi::checkout(const SHA& sha) {
		QStringList args;
		args << "checkout";
		args << sha.sha();
		// QTextStream(stdout) << "make checkout commit: " << sha.sha() << endl;
		mProcess.run(programm, args);
	}
	
	void GitApi::checkout(Branch branch) {
		QStringList args;
		args << "checkout";
		args << branch.name();
		// QTextStream(stdout) << "make checkout branch: " << branch.name() << endl;
		mProcess.run(programm, args);
	}
	
	void GitApi::setRootPathRepository(const QString &workdir) {
		if (workdir.isEmpty())
			mProcess.setWorkDirectory(QString("."));
		else
			mProcess.setWorkDirectory(workdir);
		QString rootPathRepo;
		rootPathRepo = mProcess.run(programm, QStringList() << "rev-parse" << "--show-toplevel");
		rootPathRepo = rootPathRepo.mid(0, rootPathRepo.indexOf("\n"));
		if (fatalErrorExist(rootPathRepo) || rootPathRepo.isEmpty()) {
			throw std::invalid_argument(("GitApi::GitApi(const QString&) => No git repo in path: " + workdir).toStdString());
		}
		mProcess.setWorkDirectory(rootPathRepo);
		mRootGitPath = rootPathRepo;
	}

	std::list<Branch> GitApi::branchList() {
		QStringList arg;
		arg << "branch";
		arg << "-v";
		arg << "--no-abbrev";

		// Get list of branch
		QStringList listBranch{mProcess.run(programm, arg).split('\n')};
		if (listBranch.isEmpty())
			return std::list<Branch>{};
		
		std::list<Branch> branches;
		for(auto &line : listBranch) {
			if (line.isEmpty())
				continue;
			QString nameBranch{findHEADdetachedBranch(line)};
			if (nameBranch.isEmpty()) {
				nameBranch = findNameBranch(line);
			}
			QString shaBranch{findSHAFromString(line)};
			branches.push_back(Branch{shaBranch, nameBranch});
		}
		return std::move(branches);
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
		
		// Create branch whith structure like a tree
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
