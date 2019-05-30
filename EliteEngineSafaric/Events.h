//Events.h
#pragma once

#include <vector>

#include "Delegate.h"

template< typename E >
class Events
{
public:

    template< void ( *Function )( E ) >
    static void addListener()
    {
        Delegate<E> d;
        d.bind< Function >();
        _delegates.push_back( d );
    }

    template< class C, void ( C::*Function )( E ) >
    static void addListener( C* instance )
    {
        Delegate<E> d;
        d.bind< C, Function >( instance );
        _delegates.push_back( d );
    }

    static void emit( E eventArgs )
    {
        for( size_t i = 0; i < _delegates.size(); ++i )
        {
            _delegates[i].invoke( eventArgs );
        }
    }

    template< void ( *Function )( E ) >
    static void removeListener()
    {
        Delegate<E> d;
        d.bind< Function >();

        int eraseAt = -1;
        for( size_t i = 0; i < _delegates.size(); ++i )
        {
            if( _delegates[i] == d )
            {
                eraseAt = i;
                break;
            }
        }
        if( eraseAt > -1 )
        {
            _delegates.erase( _delegates.begin() + eraseAt );
        }
    }

    template <typename C, void(C::*Function)(E)>
    static void removeListener( C* instance )
    {
        Delegate<E> d;
        d.bind< C, Function >( instance );

        int eraseAt = -1;
        for( size_t i = 0; i < _delegates.size(); ++i )
        {
            if( _delegates[i] == d )
            {
                eraseAt = i;
                break;
            }
        }
        if( eraseAt > -1 )
        {
            _delegates.erase( _delegates.begin() + eraseAt );
        }
    }

private:
    static std::vector< Delegate<E> > _delegates;

};

//Statics
template< typename E >
std::vector< Delegate<E> > Events<E>::_delegates;