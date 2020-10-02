#ifndef MAIN_CXX
#define MAIN_CXX

#include <new>

#ifndef MAIN_HXX
#include <Main.hxx>
#endif

namespace Main
{
#line 242 "ComTest.mfog"
    void App::TestShared()
    {
#line 252
        Shared::Ptr < Dumb > s0a;
#line 254
        ;
        {
#line 255
            Shared::Ptr < Dumber > s1a;
            Shared::Ptr < Dumb > s1b;
#line 258
            ;
            ;
            s1b = Shared::Ptr < Dumb > ().WrapObject(new Dumb);
#line 262
            ;
            s1a = s1b.As < Dumber > ();
#line 265
            ;
            {
                Shared::Ptr < Dumber > s2;
#line 269
                ;
#line 269
                s2 = s1a;
#line 271
                ;
#line 271
                s0a = s2.As < Dumb > ();
#line 273
                ;
            }
            ;
        }
        ;
    };
    
#line 235
    App::Dumber::~Dumber()
    {
#line 235
        ;
    };
    
#line 76 "../../src/Com/Meta.fog"
    App::SomeRefTuple2::SomeRefTuple2(int& a, double& b)
    :
        a(a),
        b(b)
    {};
    
#line 77
    Text::String App::SomeRefTuple2::AsString() const
    {
#line 77
        return Text::ToString(a) + ", " + Text::ToString(b);
    };
    
#line 57
    Text::String App::SomeTuple2::AsString() const
    {
#line 57
        return Text::ToString(a) + ", " + Text::ToString(b);
    };
    
#line 30 "ComTest.mfog"
    App::VirtualBase::~VirtualBase() {};
    
};

#endif
