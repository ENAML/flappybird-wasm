#pragma once


template<typename T>
class Singleton
{
public:
    Singleton() { }

    static T* getInstance()
    {
        static T mInstance;
        return &mInstance;
    }
};

