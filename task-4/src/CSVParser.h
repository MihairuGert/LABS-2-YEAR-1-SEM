#pragma once

#include "fstream"
#include "iostream"
#include "sstream"
#include "tuple"
#include "vector"
#include "algorithm"
#include "stdexcept"

template<int Index, typename First, typename... Args>
struct TupleGetter{
    static std::tuple<First, Args...> getTuple(std::vector<std::string>& line) {
        First temp;
        std::stringstream ss(line[Index]);
        ss >> temp;
        return std::tuple_cat(std::make_tuple(temp), TupleGetter<Index - 1, Args...>::getTuple(line));
    }
};

template<int Index, typename... Args>
struct TupleGetter<Index, std::string, Args...> {
    static std::tuple<std::string, Args...> getTuple(std::vector<std::string>& line) {
        std::string temp = line[Index];
        return std::tuple_cat(std::make_tuple(temp), TupleGetter<Index - 1, Args...>::getTuple(line));
    }
};

template<typename First, typename... Args>
struct TupleGetter<0, First, Args...>{
    static std::tuple<First, Args...> getTuple(std::vector<std::string>& line) {
        First temp;
        std::stringstream ss(line[0]);
        ss >> temp;
        return std::make_tuple(temp);
    }
};

template<typename... Args>
struct TupleGetter<0, std::string, Args...> {
    static std::tuple<std::string, Args...> getTuple(std::vector<std::string>& line) {
        std::string temp = line[0];
        return std::make_tuple(temp);
    }
};

template<typename... Args>
class CSVParser {
    std::istream& in;
    char columnDelim = ';';
    char rowDelim = '\n';
    char escapeChar = '"';
    bool isEof = false;
    size_t rowCount;
    std::string getLine();
    std::string getLine(std::stringstream& ss, char delim);
    std::vector<std::string> getWords(std::stringstream& ss);
    std::tuple<Args...> getTuple();
public:
    explicit CSVParser(std::istream& in, size_t offset = 0, char columnDelim = ';', char rowDelim = '\n', char escapeChar = '"')
            : in(in), columnDelim(columnDelim), rowDelim(rowDelim), escapeChar(escapeChar) {
        rowCount = 0;
        for (int i = 0; i < offset; ++i) {
            getLine();
        }
    };
    // Input iterator.
    class Iterator : public std::iterator<std::input_iterator_tag, std::tuple<Args...>> {
        CSVParser* parser;
        std::tuple<Args...> current;
        bool isEnd;
    public:
        explicit Iterator(CSVParser* parser, bool isEnd = false) : parser(parser), isEnd(isEnd) {
            if (!isEnd) {
                ++(*this);
            }
        }
        Iterator& operator++() {
            if (parser->isEof) isEnd = true;
            if (isEnd) return *this;
            current = parser->getTuple();
            if (parser->in.eof()) {
                parser->isEof = true;
            }
            return *this;
        }
        bool operator!=(const Iterator& it) const {
            return isEnd != it.isEnd;
        }
        std::tuple<Args...>& operator*() {
            return current;
        }
        std::tuple<Args...>* operator->() {
            return &current;
        }
    };
    // CSV Parser.
    Iterator begin() {
        return Iterator(this);
    }
    Iterator end() {
        return Iterator(this, true);
    }
};

template<typename... Args>
std::tuple<Args...> CSVParser<Args...>::getTuple() {
    rowCount++;
    std::string row = getLine();
    if (row.empty()) {
        throw std::length_error("Empty document.");
    }
    std::stringstream ss(row);
    std::string buffer;
    std::tuple<Args...> tuple;
    std::vector<std::string> words;
    words = getWords(ss);
    std::reverse(words.begin(), words.end());
    if (words.size() != sizeof...(Args)) {
        throw std::length_error("Too many or too few columns in row #" + std::to_string(rowCount));
    }
    tuple = TupleGetter<sizeof...(Args) - 1, Args...>::getTuple(words);
    return tuple;
}

template<typename... Args>
std::string CSVParser<Args...>::getLine(std::stringstream& ss, char delim) {
    std::string buffer;
    char ch;
    bool isEscape = false;
    while (ss.read(&ch, sizeof(char))) {
        if (ch == delim && !isEscape) {
            break;
        }
        if (ch != delim && isEscape) {
            buffer.push_back(escapeChar);
        }
        if (ch == escapeChar) {
            isEscape = true;
            continue;
        } else {
            isEscape = false;
        }
        buffer.push_back(ch);
    }
    return buffer;
}

template<typename... Args>
std::string CSVParser<Args...>::getLine() {
    std::string buffer;
    char ch;
    bool isEscape = false;
    while (in.read(&ch, sizeof(char))) {
        if (ch == rowDelim && !isEscape) {
            break;
        }
        if (ch != rowDelim && isEscape) {
            buffer.push_back(escapeChar);
        }
        if (ch == escapeChar) {
            isEscape = true;
            continue;
        } else {
            isEscape = false;
        }
        buffer.push_back(ch);
    }
    return buffer;
}

template<typename... Args>
std::vector<std::string> CSVParser<Args...>::getWords(std::stringstream& ss) {
    std::string buffer;
    std::vector<std::string> result;
    while(true) {
        buffer = getLine(ss, columnDelim);
        if (buffer.empty()) {
            break;
        }
        result.emplace_back(buffer);

    }
    return result;
}