#pragma once
#include "../third_party/incldue/sqlite3/sqlite3.h"
#include <iostream>
#include <string>
#include <codecvt>
#include <locale>
#pragma warning(disable:4996)
class SQLiteWrapper {
public:
    SQLiteWrapper(const std::string& db_name) : current_id(0) {
        int rc = sqlite3_open(db_name.c_str(), &db);
        if (rc) {
            std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
            db = nullptr;
        }
        else {
            std::cout << "Opened database successfully" << std::endl;
            createTable();
            updateCurrentId();
        }
    }

    ~SQLiteWrapper() {
        if (db) {
            sqlite3_close(db);
        }
    }

    bool storeWString(const std::wstring& wstr) {
        if (!db) return false;

        std::string str = wstringToUtf8(wstr);
        const char* sql = "INSERT INTO STRINGS (CONTENT) VALUES (?);";
        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }

        sqlite3_bind_text(stmt, 1, str.c_str(), -1, SQLITE_STATIC);
        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            std::cerr << "Execution failed: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            return false;
        }

        sqlite3_finalize(stmt);
        updateCurrentId();
        return true;
    }

    std::wstring getWStringById(int id) {
        if (!db) return L"";

        const char* sql = "SELECT CONTENT FROM STRINGS WHERE ID = ?;";
        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
            return L"";
        }

        sqlite3_bind_int(stmt, 1, id);
        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            std::string result = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            sqlite3_finalize(stmt);
            return utf8ToWstring(result);
        }
        else {
            sqlite3_finalize(stmt);
            return L"";
        }
    }

    int getCurrentId() const {
        return current_id;
    }

    bool clearDatabase() 
    {
        if (!db) return false;

        const char* sql = "DELETE FROM STRINGS;";
        char* errMsg = nullptr;
        int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
        if (rc != SQLITE_OK) 
        {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            return false;
        }

        updateCurrentId();
        return true;
    }

private:
    sqlite3* db;
    int current_id;

    void createTable() {
        const char* sql = "CREATE TABLE IF NOT EXISTS STRINGS (" \
            "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
            "CONTENT TEXT NOT NULL);";
        char* errMsg = nullptr;
        int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }
    }

    void updateCurrentId() {
        const char* sql = "SELECT MAX(ID) FROM STRINGS;";
        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
            current_id = 0;
            return;
        }

        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            current_id = sqlite3_column_int(stmt, 0);
        }
        else {
            current_id = 0;
        }
        sqlite3_finalize(stmt);
    }

    std::string wstringToUtf8(const std::wstring& wstr) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
        return conv.to_bytes(wstr);
    }

    std::wstring utf8ToWstring(const std::string& str) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
        return conv.from_bytes(str);
    }
};

//int main() {
//    SQLiteWrapper db("example.db");
//
//    // ´æ´¢¿í×Ö·û´®
//    db.storeWString(L"Hello, World!");
//    db.storeWString(L"ÁíÒ»¸ö×Ö·û´®");
//
//    // »ñÈ¡µ±Ç°ID
//    int currentId = db.getCurrentId();
//    std::cout << "Current ID: " << currentId << std::endl;
//
//    // ²éÑ¯¿í×Ö·û´®
//    std::wstring wstr1 = db.getWStringById(1);
//    std::wstring wstr2 = db.getWStringById(2);
//
//    std::wcout << L"String with ID 1: " << wstr1 << std::endl;
//    std::wcout << L"String with ID 2: " << wstr2 << std::endl;
//
//    // Çå¿ÕÊý¾Ý¿â
//    db.clearDatabase();
//    std::cout << "Database cleared." << std::endl;
//
//    return 0;
//}
