#pragma once


template<class T>
class Optional
{
protected:
    T    mValue;
    bool mEngaged;

public:
    Optional() : mEngaged(false)                       { }
    Optional(const T& a) : mValue(a), mEngaged(true)   { }

    const T& operator*() const  { assert(mEngaged); return mValue; }
    T& operator*()              { assert(mEngaged); return mValue; }

    const T* operator->() const { assert(mEngaged); return &mValue; }
    T* operator->()             { assert(mEngaged); return &mValue; }

    operator bool() const       { return mEngaged; }
};

