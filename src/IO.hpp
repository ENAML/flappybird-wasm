/**
 * -----------------------------------------------------------------------------
 * IO
 * -----------------------------------------------------------------------------
 */
#pragma once

class IO
{
public:
    static void loadConfig(const char *path);
    static char *loadFileBuffer(const char *path);
    static void freeFileBuffer(char *buffer);
    static void loadJSON(const char *path);

    // class FileBuffer
    // {
    // private:
    //     // char *filePath = NULL;
    //     // bool loaded = false;
    //     char *data = NULL;
    //     long size = 0;
    
    // public:
    //     // constructor
    //     FileBuffer(const char *filePath)
    //     {
    //         FILE *file = fopen(filePath, "rb");

    //         if (!file)
    //             die("could not open file");

    //         // if (file) {
    //         fseek(file, 0, SEEK_END);
    //         this->size = ftell (file);
    //         fseek(file, 0, SEEK_SET);

    //         this->data = new char[this->size];

    //         fread(this->data, 1, this->size, file);        
    //         fclose(file);
    //         // }
    //     }

    //     // destructor
    //     ~FileBuffer() 
    //     {
    //         delete[] data;
    //     }

    //     // copy constructor 
    //     FileBuffer(const FileBuffer& s) 
    //     {
    //         this->size = s.size;
            
    //         data = new char[this->size];
    //         strcpy(data, s.data);
    //     }

    //     // copy assignment
    //     FileBuffer& operator=(const FileBuffer& rhs)
    //     {
    //         if (this == &rhs) {
    //             return *this;
    //         }

    //         // first, deallocate memory that 'this' used to hold
    //         delete[] data;

    //         // now copy from rhs
    //         this->size = rhs.size;
    //         this->data = new char[this->size];
    //         strcpy(data, rhs.data);

    //         return *this;
    //     }


    //     const char *getData()
    //     {
    //         assert(this->data != NULL);
            
    //         return this->data;
    //     }

    //     long getSize()
    //     {
    //         return this->size;
    //     }
    // };
};