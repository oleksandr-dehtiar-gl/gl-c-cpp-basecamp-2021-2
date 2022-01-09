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
		static bool fatalErrorExist(const QString& gitApiOutString);
	public:
		const QString& getWorkDirectory() { return mRootGitPath; }
		std::list<Branch> branchList();
		sharedTreeCommitNode getRootCommitTree();
		QString commitChanges(const SHA &sha);
		void checkout(const SHA& sha);
		Commit getActiveCommit();
		Branch getActiveBranch();
		std::list<Commit> getCommitsWhenTextChanged(const QString& text);
	public:
		static QString cloneRepository(QString url, QString path);
	private:
		Process mProcess;
		QString mRootGitPath;
	};

}

#endif // GITAPI_HPP