#ifndef GITAPI_HPP
#define GITAPI_HPP

#include <list>

#include "process.hpp"
#include "gitObjects.hpp"
#include "treeCommitNode.hpp"

namespace gitgui {
	
	class GitApi {
	public:
		explicit GitApi(const QString& workdir = QString("."));
		GitApi(const GitApi&) = delete;
		GitApi& operator=(const GitApi&) = delete;
	private:
		void setRootPathRepository(const QString &workdir);
		QString findSHAFromString(const QString& str);
		QString findStarsActiveBranch(const QString& str);
		QString findHEADdetachedBranch(const QString& str);
		QString findNameBranch(const QString& str);
	private: // Static methods
		static bool fatalErrorExist(const QString& gitApiOutString);
		static QString getPathFromURL(const QString& url);
	public:
		static QString cloneRepository(QString url, QString path);
	public:
		const QString& getWorkDirectory() { return mRootGitPath; }
		std::list<Branch> branchList();
		sharedTreeCommitNode getRootCommitTree();
		QString commitChanges(const SHA &sha);
		void checkout(const SHA& sha);
		void checkout(Branch branch);
		Commit getActiveCommit();
		Branch getActiveBranch();
		std::list<Commit> getCommitsWhenTextChanged(const QString& text);
		std::list<IndexFile> getIndexFilesList();
		void addToIndexStage(const std::list<IndexFile> &fileList);
		void removeFromIndexStage(const std::list<IndexFile> &fileList);
		QString makeCommit(const QString& msg);
	private:
		Process mProcess;
		QString mRootGitPath;
	};

}

#endif // GITAPI_HPP
