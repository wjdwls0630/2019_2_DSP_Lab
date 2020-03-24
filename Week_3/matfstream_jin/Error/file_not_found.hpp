//
// Created by ParkJungJin on 2019-10-02.
//

#ifndef _FILENOTFOUND_HPP
#define _FILENOTFOUND_HPP

class FileNotFound : public std::exception{
private:
    std::string message;
public:
    FileNotFound(const std::string &t_FileName):
    message("FileNotFound : "+t_FileName+" is not found!"){}

    const char* what() const throw(){
        return message.c_str();
    }
};

#endif //_FILENOTFOUND_HPP
