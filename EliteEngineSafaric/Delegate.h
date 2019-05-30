//Delegate.h
#pragma once

template< typename T >
class Delegate
{
    typedef void* InstancePtr;
    typedef void (*InternalFunction)(InstancePtr, T);
    
    InstancePtr instancePtr;
    InternalFunction internalFunction;
 
public:
    Delegate(void) : instancePtr(nullptr), internalFunction(nullptr) {}
 
    //Converts a free function into an internal function
    template< void (*Function)( T ) >
    static void freeFunctionWrapper( InstancePtr, T arg )
    {
        //No need to use an instance in a free-standing function
        ( Function )( arg ); 
    }
 
    //Safely converts an instance method into an internal function
    template< class C, void ( C::*Function )( T ) >
    static void instanceMethodWrapper( InstancePtr instance, T arg )
    {
        //Cast the instance pointer back into the original class
        ( static_cast< C* >( instance )->*Function )( arg );
    }

    //Bind a free-standing function
    template< void ( *Function )( T )>
    void bind( void )
    {
        instancePtr = nullptr; //No instance in a free-standing function
        internalFunction = &freeFunctionWrapper< Function >;
    }
 
    //Binds an instance method
    template< typename C, void ( C::*Function )( T ) >
    void bind( C* instance )
    {
        instancePtr = instance;
        internalFunction = &instanceMethodWrapper< C, Function >;
    }

    void invoke( T arg )
    {
        internalFunction( instancePtr, arg );
    }

    bool operator==( const Delegate& other )
    {
        return instancePtr == other.instancePtr && internalFunction == other.internalFunction ;
    }
};