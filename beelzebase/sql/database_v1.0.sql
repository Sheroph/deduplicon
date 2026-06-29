BEGIN;

CREATE TABLE IF NOT EXISTS migrations (
    version INTEGER PRIMARY KEY,
    applied_at TIMESTAMP NOT NULL,
    migration_topic VARCHAR(20) NOT NULL
);

CREATE TABLE IF NOT EXISTS monitored_fs (
    file_path VARCHAR(4096) PRIMARY KEY,
    file_size BIGINT NOT NULL,
    file_hash VARCHAR(1024),
    last_hash_update TIMESTAMP
);

CREATE TABLE If NOT EXISTS similarity (
    file_path_right VARCHAR(4096) NOT NULL,
    file_path_left VARCHAR(4096) NOT NULL,
    similarity_percent FLOAT NOT NULL,

    PRIMARY KEY (file_path_right, file_path_left),
    FOREIGN KEY (file_path_left) REFERENCES monitored_fs(file_path),
    FOREIGN KEY (file_path_right) REFERENCES monitored_fs(file_path)
);

CREATE TABLE IF NOT EXISTS settings (
    key VARCHAR(4096) PRIMARY KEY,
    value TEXT NOT NULL
);

COMMIT;
