/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <pierrevr@mindgoo.be> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Pierre Vorhagen
 * ----------------------------------------------------------------------------
 */

#include <fstream>

#include "CsvFile.hpp"

bool CsvFile::load(const char * path) {
    std::ifstream ifs(path);

    if (!ifs) {
        return false;
    }

    _data.clear();

    std::string line;

    while (getline(ifs, line, '\n')) {
        int i = 0;
        std::vector< std::string > vector;

        while (line[i]) {
            std::string field;

            while (line[i] && line[i] != ',') {
                field.push_back(line[i]);
                i++;
            }

            if (line[i] == ',') {
                i++;
            }

            vector.push_back(field);
        }

        _data.push_back(vector);
    }

    ifs.close();

    return true;
}

bool CsvFile::save(const char * path) const {
    std::ofstream ofs(path);

    if (!ofs) {
        return false;
    }

    std::list< std::vector< std::string > >::const_iterator row;

    for (row = _data.begin(); row != _data.end(); row++) {
        std::vector< std::string >::const_iterator col = row->begin();

        if (col != row->end()) {
            ofs << *col;

            col++;

            for (; col != row->end(); col++) {
                ofs << ',' << *col;
            }

            ofs << '\n';
        }
    }

    ofs.close();

    return true;
}

bool CsvFile::add(const std::vector< std::string > & row) {
    std::vector< std::string >::const_iterator it;

    for (it = row.begin(); it != row.end(); it++) {
        if (it->find(',') != std::string::npos) {
            return false;
        }
    }

    _data.push_back(row);

    return true;
}

bool CsvFile::remove(unsigned int n) {
    if (n > _data.size()) {
        return false;
    }

    std::list< std::vector< std::string > >::iterator row = _data.begin();

    for (unsigned int i = 0; i < n; i++) {
        row++;
    }

    _data.erase(row);

    return true;
}

std::list< std::vector< std::string > > CsvFile::get() const {
    return _data;
}
