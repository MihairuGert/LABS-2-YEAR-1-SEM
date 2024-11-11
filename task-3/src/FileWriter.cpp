#include "FileWriter.h"

void FileWriter::writeBinaryInFile(std::ostream &out, int value, int bytes) {
    out.write(reinterpret_cast<const char*>(&value), bytes);
}
