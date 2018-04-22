/**
 * -----------------------------------------------------------------------------
 * events
 * ------
 * see: see: https://stackoverflow.com/a/14189561
 * -----------------------------------------------------------------------------
 */
#pragma once

#include <vector>
#include <algorithm>
#include <functional>
#include <stdio.h>


template<class T>
class EventEmitter 
{
    using Callback = std::function<void (T)>;

private:
    // just a small struct to wrap the callbacks with a
    // reference ID so I can remove them from an emitter
    // without caching the callback itself.
    // 
    // TODO: this is probably not good design...
    struct CallbackWrapper {
        int id;
        Callback callback;
    };

    std::vector<CallbackWrapper> mCallbacks;

    int idTicker;

public:
    EventEmitter()
    : idTicker(0)
    {}

    int addListener(Callback callback)
    {
        // printf("size: %i\n", this->mCallbacks.size());
        int idRef = this->idTicker++;

        this->mCallbacks.push_back(
            CallbackWrapper{idRef, callback}
        );

        return idRef;
    }

    void removeListener(int idRef)
    {
        // printf("size: %i\n", this->mCallbacks.size());
        // this->mCallbacks.push_back(callback);

        // https://stackoverflow.com/a/9053941
        auto iter = std::remove_if(
            this->mCallbacks.begin(),
            this->mCallbacks.end(),
            [&](CallbackWrapper &wrapper) {
                return wrapper.id == idRef;
            }
        );

        this->mCallbacks.erase(iter, this->mCallbacks.end());
    }

    void removeAllListeners()
    {
        this->mCallbacks.clear();
    }

    int listenerCount()
    {
        return this->mCallbacks.size();
    }

    void emit(T t)
    {
        for (auto &wrapper : this->mCallbacks)
        {
            wrapper.callback(t);
        }
    }
};





