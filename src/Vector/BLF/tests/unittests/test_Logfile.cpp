#define BOOST_TEST_MODULE Logfile
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <boost/filesystem.hpp>

#include "Vector/BLF/File.h"

#define SUCCEEDED(code) ((int)(code) >= 0)
#define WARNED(code) ((int)(code) & 0x40000000)
#define FAILED(code) ((int)(code) < 0)

BOOST_AUTO_TEST_CASE(Logfile)
{
    Vector::BLF::File infile;
    Vector::BLF::File outfile;

    /* input log file */
    boost::filesystem::path inpath(CMAKE_CURRENT_SOURCE_DIR "/data/logfile.blf");
    std::string infilename = inpath.string();
    infile.open(infilename);
    BOOST_REQUIRE(infile.is_open());

    /* FileStatistics */
    BOOST_REQUIRE(infile.fileStatistics.signature == Vector::BLF::FileSignature);
#define SHOW_FILE_STATISTICS
#ifdef SHOW_FILE_STATISTICS
    /* show file statistics */
    std::cout << "signature: 0x" << std::hex << infile.fileStatistics.signature << std::endl;
    std::cout << "applicationName: " << infile.fileStatistics.applicationName() << std::endl;
    std::cout << "applicationNumber: " << std::dec << (unsigned short) infile.fileStatistics.applicationMajor << "." << (unsigned short) infile.fileStatistics.applicationMinor << "." << (unsigned short) infile.fileStatistics.applicationBuild << std::endl;
    std::cout << "apiNumber: " << std::dec << (unsigned short) infile.fileStatistics.apiMajor << "." << (unsigned short) infile.fileStatistics.apiMinor << "." << (unsigned short) infile.fileStatistics.apiBuild << "." << (unsigned short) infile.fileStatistics.apiPatch << std::endl;
    std::cout << "fileSize: " << std::dec << infile.fileStatistics.fileSize << " = 0x" << std::hex << infile.fileStatistics.fileSize << std::endl;
    std::cout << "uncompressedFileSize: " << std::dec << infile.fileStatistics.uncompressedFileSize << " = 0x" << std::hex << infile.fileStatistics.uncompressedFileSize << std::endl;
    std::cout << "objectCount: " << std::dec << infile.fileStatistics.objectCount << std::endl;
    std::cout << "objectsRead: " << std::dec << infile.fileStatistics.objectsRead << std::endl;
    std::cout << "measurementStartTime: " << std::dec
              << infile.fileStatistics.measurementStartTime.year << "-" << infile.fileStatistics.measurementStartTime.month << "-" << infile.fileStatistics.measurementStartTime.day << " (" << infile.fileStatistics.measurementStartTime.dayOfWeek << ") "
              << infile.fileStatistics.measurementStartTime.hour << ":" << infile.fileStatistics.measurementStartTime.minute << ":" << infile.fileStatistics.measurementStartTime.second << "+" << infile.fileStatistics.measurementStartTime.milliseconds << "ms" << std::endl;
    std::cout << "lastObjectTime: " << std::dec
              << infile.fileStatistics.lastObjectTime.year << "-" << infile.fileStatistics.lastObjectTime.month << "-" << infile.fileStatistics.lastObjectTime.day << " (" << infile.fileStatistics.lastObjectTime.dayOfWeek << ") "
              << infile.fileStatistics.lastObjectTime.hour << ":" << infile.fileStatistics.lastObjectTime.minute << ":" << infile.fileStatistics.lastObjectTime.second << "+" << infile.fileStatistics.lastObjectTime.milliseconds << "ms" << std::endl;
#endif

#ifdef OUTFILE_EXISTS
    /* create output directory */
    boost::filesystem::path outdir(CMAKE_CURRENT_BINARY_DIR "/data/");
    if (!exists(outdir)) {
        BOOST_REQUIRE(create_directory(outdir));
    }

    /* output log file */
    boost::filesystem::path outpath(CMAKE_CURRENT_BINARY_DIR "/data/logfile.blf");
    std::string outfilename = outpath.string();
    outfile.open(outfilename);
    outfile.fileStatistics = infile.fileStatistics;
    // outfile.write(fileStatistics);
#endif

    /* go through all records */
    while(!infile.eof()) {
        Vector::BLF::ObjectHeaderBase * ohb = infile.read();
        if (ohb == nullptr) {
            std::cerr << "obj == nullptr at currentObjectCount=" << std::dec << infile.currentObjectCount << std::endl;
            continue;
        }

#ifdef OUTFILE_EXISTS
        outfile.write(ohb);
#endif

        delete ohb;
    }

    /* show file statistics */
    //std::cout << "currentUncompressedFileSize: " << std::dec << infile.currentUncompressedFileSize << " = 0x" << std::hex << infile.currentUncompressedFileSize << std::endl;
    BOOST_CHECK(infile.fileStatistics.uncompressedFileSize == infile.currentUncompressedFileSize);
    //std::cout << "currentObjectCount: " << std::dec << (infile.currentObjectCount + 1) << " = 0x" << std::hex << (infile.currentObjectCount + 1) << std::endl;
    BOOST_CHECK(infile.fileStatistics.objectCount == (infile.currentObjectCount + 1));

    /* input and output log file should be equivalent */
#ifdef OUTFILE_EXISTS
    std::ifstream ifs1(inpath.c_str());
    std::ifstream ifs2(outpath.c_str());
    std::istream_iterator<char> b1(ifs1), e1;
    std::istream_iterator<char> b2(ifs2), e2;
    BOOST_CHECK_EQUAL_COLLECTIONS(b1, e1, b2, e2);
#endif
}
