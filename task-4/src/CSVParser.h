#pragma once

#include "fstream"
#include "iostream"
#include "sstream"
#include "tuple"
#include "vector"
#include "algorithm"

template<int Index, typename First, typename... Args>
struct TupleGetter{
    static std::tuple<First, Args...> getTuple(std::vector<std::string>& line) {
        First temp;
        std::stringstream ss(line[Index]);
        ss >> temp;
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
class CSVParser {
    std::istream& in;
    char columnDelim = ';';
    char rowDelim = '\n';
    // TODO WINDOW
    std::string getLine();
    std::tuple<Args...> getTuple();
public:
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
            if (isEnd) return *this;
            current = parser->getTuple();
            if (parser->in.eof()) {
                isEnd = true;
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
    explicit CSVParser(std::istream& in, size_t offset = 0) : in(in) {
        for (int i = 0; i < offset; ++i) {
            getLine();
        }
    };
};

template<typename... Args>
std::tuple<Args...> CSVParser<Args...>::getTuple() {
    std::string row = getLine();
    if (row.empty()) {
        return std::tuple<Args...>();
    }
    std::stringstream ss(row);
    std::string buffer;
    std::tuple<Args...> tuple;
    std::vector<std::string> words;
    while(std::getline(ss, buffer, columnDelim)) {
        words.push_back(buffer);
    }
    std::reverse(words.begin(), words.end());
    tuple = TupleGetter<sizeof...(Args) - 1, Args...>::getTuple(words);
    return tuple;
}

template<typename... Args>
std::string CSVParser<Args...>::getLine() {
    std::string buffer;
    std::getline(in, buffer, rowDelim);
    return buffer;
}
