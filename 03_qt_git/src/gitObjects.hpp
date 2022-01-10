#ifndef GITOBJECTS_HPP
#define GITOBJECTS_HPP

#include <QtWidgets>

namespace gitgui {
	
	// Special commit's name
	constexpr char allCommit[] = "All";
	constexpr char treeCommit[] = "Tree";
	
	enum GitObjectType {
		COMMIT = 0,
		BRANCH,
		SHA_T
	};

	class SHA {
	protected:
		SHA(const QString &sha, GitObjectType type) : mSHA(sha), mType(type) {}
	public:
		virtual ~SHA() {}
	public:
		QString sha() const { return mSHA; }
		GitObjectType type() const { return mType; }
		SHA getShaObject() { return *this; }
	private:
		QString mSHA;
		GitObjectType mType;
	};
	
	class Commit : public SHA {
	public:
		explicit Commit(QString sha) : SHA(sha, GitObjectType::COMMIT) { }
	};
	
	class Branch : public SHA {
	public:
		explicit Branch(QString sha, QString name) : SHA(sha, GitObjectType::BRANCH), mBranchName(name) { }
	public:	
		const QString& name() const { return mBranchName; }
	private:
		QString mBranchName;
	};
	
	enum IndexType {
		INDEX = 0,
		NO_INDEX
	};
	
	class IndexFile {
	public:
		IndexFile() : mType(IndexType::NO_INDEX) {}
		explicit IndexFile(const QString& name, IndexType type = IndexType::NO_INDEX) : mName(name), mType(type) {}
		IndexFile(IndexFile&& file) { mName.swap(file.mName); mType = file.mType; }
		IndexFile(const IndexFile& file) : mName(file.mName), mType(file.mType) { }
	public:
		bool isIndexed() const { return mType == IndexType::INDEX; }
		void setIndexed() { mType = IndexType::INDEX; }
		void setNotIndexed() { mType = IndexType::NO_INDEX; }
		const QString& name() const { return mName; }
	private:
		QString mName;
		IndexType mType;
	};
	
}

#endif // GITOBJECTS_HPP
