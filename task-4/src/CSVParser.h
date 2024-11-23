#pragma once

#include "fstream"
#include "sstream"
#include "tuple"

template<typename... Args>
class CSVParser;

template<typename... Args>
class CSVParserIterator : public std::iterator<std::input_iterator_tag, std::tuple<Args...>> {
    friend class CSVParser<Args...>;
private:
    explicit CSVParserIterator(std::tuple<Args...>* p);
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
    // Add here line;
}

template<typename... Args>
class CSVParser {
    std::istream& in;
    char columnDelim = ';';
    char rowDelim = '\n';
    // TODO EKRANIROVANIE
    //
    //
    size_t offset;
    std::string getLine();
    void setTupleElement(int count, std::tuple<Args...>, std::stringstream buffer);
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
    // TODO SOMEHOW PARSE THE LINES
//    while(std::getline(ss, buffer, columnDelim)) {
//         tuple = std::tuple_cat(tuple, std::make_tuple<Args>(buffer));
//    }
    return std::tuple<Args...>();
}

template<typename... Args>
std::string CSVParser<Args...>::getLine() {
    std::string buffer;
    std::getline(in, buffer, rowDelim);
    return buffer;
}


