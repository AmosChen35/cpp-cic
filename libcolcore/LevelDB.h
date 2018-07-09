#ifndef LIBCOLCORE_LEVELDB_H
#define LIBCOLCORE_LEVELDB_H

namespace db
{

class LevelDB : public DatabaseFace
{
public:
    static leveldb::ReadOptions defaultReadOptions();
    static leveldb::WriteOptions defaultWriteOptions();
    static leveldb::Options defaultDBOptions();

    explicit LevelDB(boost::filesystem::path const& _path,
        leveldb::ReadOptions _readOptions = defaultReadOptions(),
        leveldb::WriteOptions _writeOptions = defaultWriteOptions(),
        leveldb::Options _dbOptions = defaultDBOptions());

    std::string lookup(Slice _key) const override;
    bool exists(Slice _key) const override;
    void insert(Slice _key, Slice _value) override;
    void kill(Slice _key) override;

    std::unique_ptr<WriteBatchFace> createWriteBatch() const override;
    void commit(std::unique_ptr<WriteBatchFace> _batch) override;

    void forEach(std::function<bool(Slice, Slice)> f) const override;

private:
    std::unique_ptr<leveldb::DB> m_db;
    leveldb::ReadOptions const m_readOptions;
    leveldb::WriteOptions const m_writeOptions;
};

class LevelDBWriteBatch : public WriteBatchFace
{
public:
    void insert(Slice _key, Slice _value) override;
    void kill(Slice _key) override;

    leveldb::WriteBatch const& writeBatch() const { return m_writeBatch; }
    leveldb::WriteBatch& writeBatch() { return m_writeBatch; }

private:
    leveldb::WriteBatch m_writeBatch;
};

} //namespace db

#endif //LIBCOLCORE_LEVELDB_H
