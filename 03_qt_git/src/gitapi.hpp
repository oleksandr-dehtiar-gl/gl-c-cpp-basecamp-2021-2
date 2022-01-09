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
		QString findSHABranch(const QString& str);
		QString findStarsActiveBranch(const QString& str);
		QString findHEADdetachedBranch(const QString& str);
		QString findNameBranch(const QString& str);
	private: // Static methods
		static QString regExpression(const QRegExp& regex, const QString& str);
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
	private:
		Process mProcess;
		QString mRootGitPath;
	};

}

#endif // GITAPI_HPP
