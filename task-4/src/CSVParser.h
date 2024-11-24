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
class CSVParser;

template<typename... Args>
class CSVParserIterator : public std::iterator<std::input_iterator_tag, std::tuple<Args...>> {
    friend class CSVParser<Args...>;
private:
    explicit CSVParserIterator(std::tuple<Args...>* newData);
public:
    CSVParserIterator(const CSVParserIterator &it);

    bool operator!=(CSVParserIterator const& other) const;
    typename CSVParserIterator::reference operator*() const;
    CSVParserIterator& operator++();
private:
    std::tuple<Args...>* data;
};

template<typename... Args>
typename CSVParserIterator<Args...>::reference CSVParserIterator<Args...>::operator*() const {
    return *data;
}

template<typename... Args>
CSVParserIterator<Args...>::CSVParserIterator(std::tuple<Args...> *newData) {
    data = newData;
}

template<typename... Args>
CSVParserIterator<Args...>::CSVParserIterator(const CSVParserIterator &it) {
    data = it.data;
}

template<typename... Args>
bool CSVParserIterator<Args...>::operator!=(const CSVParserIterator &other) const {
    return data != other.data;
}

template<typename... Args>
CSVParserIterator<Args...> &CSVParserIterator<Args...>::operator++() {
    (*data) = CSVParser<Args...>::getTuple();
    return *this;
}

template<typename... Args>
class CSVParser {
    std::istream& in;
    char columnDelim = ';';
    char rowDelim = '\n';
    // TODO EKRANIROVANIE
    // TODO OFFSET
    size_t offset;
    std::string getLine();
    std::tuple<Args...> getTuple();
public:
    typedef CSVParserIterator<Args...> iterator;
    CSVParser(std::istream& in, size_t offset = 0) : in(in), offset(offset) {};
};

template<typename... Args>
std::tuple<Args...> CSVParser<Args...>::getTuple() {
    std::string row = getLine();
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




