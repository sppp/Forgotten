#ifndef CHRONO_HXX
#define CHRONO_HXX

#include <new>

#ifndef MATH_HXX
#include <Math.hxx>
#endif
#ifndef NATIVE_HXX
#include <Native.hxx>
#endif

namespace Chrono
{
};

namespace Chrono {
class Time;
}

namespace Chrono
{
#line 52 "../../src/Com/Chrono.fog"
    inline Time operator+ (const Time& t, Lang::int64 seconds);
#line 282
    Text::String GetTimeDurationString(Time begin, Time end);
    
    class Date
    {
    protected:
#line 8
        short year;
        Lang::byte month;
#line 9
        Lang::byte day;
        
    public:
        inline Date();
#line 17
        bool operator== (const Date& d) const;
#line 142
        Lang::int64 Get() const;
#line 15
        void Set(Lang::int64 scalar);
#line 157
        void Set(int d);
#line 151
        void Set(int y, int m, int d);
        
    public:
#line 123
        static const int *DaysInMonth();
#line 137
        static int GetDaysOfMonth(int m, int y);
#line 133
        static bool IsLeapYear(int year);
#line 128
        static const int *MonthDayOffset();
    };
    
    class Time : public Chrono::Date
    {
#line 27
        Lang::byte hour;
#line 27
        Lang::byte min;
#line 27
        Lang::byte sec;
        
    public:
        inline Time();
        inline Time(const Time& t);
        inline Time(int y, int m, int d);
        inline Time(int y, int m, int d, int h, int min, int s);
#line 43
        bool operator== (const Time& t) const;
#line 238
        Text::String AsDiffString() const;
#line 221
        Text::String AsString() const;
#line 39
        Lang::int64 Get() const;
        Lang::uint32 GetHashValue();
#line 277
        int GetStamp() const;
#line 211
        void Set(Lang::int64 scalar);
#line 204
        void Set(int y, int mon, int d, int h, int m, int s);
#line 272
        void SetFromStamp(int seconds);
        
    public:
#line 266
        static Time GetSys();
    };
    
    class TimeStop
    {
#line 59
        Native::HighResTimePoint *tp;
        
    public:
        TimeStop();
        inline ~TimeStop();
#line 70
        Text::String AsString() const;
#line 66
        inline int Elapsed() const;
        inline double ElapsedSeconds() const;
#line 65
        inline void Reset();
#line 68
        inline int ResetElapsed();
        inline double ResetElapsedSeconds();
    };
    
    struct OnlineFrequency
    {
#line 84
        TimeStop timer;
        int ticks;
        
        inline OnlineFrequency();
#line 93
        inline double operator++ ();
#line 92
        inline operator double() const;
#line 89
        double Get() const;
#line 88
        inline void Reset();
#line 90
        inline void Tick();
    };
    
    struct OnlineFrequencyWindow
    {
#line 97
        OnlineFrequency freq0;
#line 97
        OnlineFrequency freq1;
        bool which;
        double interval;
        
        OnlineFrequencyWindow();
#line 108
        inline double operator++ ();
#line 107
        inline operator double() const;
#line 316
        double Get() const;
#line 297
        OnlineFrequency& GetActive();
#line 302
        OnlineFrequency& GetInactive();
#line 104
        inline void SwitchActive();
#line 307
        void Tick();
    };
};

namespace Chrono
{
#line 52
    inline Time operator+ (const Time& t, Lang::int64 seconds)
    {
#line 53
        Time o;
        o.Set(t.Get() + seconds);
        return o;
    };
    
#line 12
    inline Date::Date() {};
    
#line 87
    inline OnlineFrequency::OnlineFrequency()
    :
        ticks(0)
    {};
    
#line 93
    inline double OnlineFrequency::operator++ ()
    {
#line 93
        Tick();
#line 93
        return Get();
    };
    
#line 92
    inline OnlineFrequency::operator double() const
    {
#line 92
        return Get();
    };
    
#line 88
    inline void OnlineFrequency::Reset()
    {
#line 88
        timer.Reset();
#line 88
        ticks = 0;
    };
    
#line 90
    inline void OnlineFrequency::Tick()
    {
#line 90
        ticks ++ ;
    };
    
#line 108
    inline double OnlineFrequencyWindow::operator++ ()
    {
#line 108
        Tick();
#line 108
        return Get();
    };
    
#line 107
    inline OnlineFrequencyWindow::operator double() const
    {
#line 107
        return Get();
    };
    
#line 104
    inline void OnlineFrequencyWindow::SwitchActive()
    {
#line 104
        which = !which;
    };
    
#line 30
    inline Time::Time() {};
    
#line 31
    inline Time::Time(const Time& t)
    {
#line 31
        Lang::Memory::Copy(this, &t, sizeof (Time));
    };
    
#line 32
    inline Time::Time(int y, int m, int d)
    {
#line 32
        Set(y, m, d, 0, 0, 0);
    };
    
#line 33
    inline Time::Time(int y, int m, int d, int h, int min, int s)
    {
#line 33
        Set(y, m, d, h, min, s);
    };
    
#line 63
    inline TimeStop::~TimeStop()
    {
#line 63
        delete tp;
#line 63
        tp = 0;
    };
    
    inline int TimeStop::Elapsed() const
    {
#line 66
        return tp -> Elapsed();
    };
    
#line 67
    inline double TimeStop::ElapsedSeconds() const
    {
#line 67
        return tp -> ElapsedSeconds();
    };
    
#line 65
    inline void TimeStop::Reset()
    {
#line 65
        tp -> Reset();
    };
    
    inline int TimeStop::ResetElapsed()
    {
#line 68
        return tp -> ResetElapsed();
    };
    
#line 69
    inline double TimeStop::ResetElapsedSeconds()
    {
#line 69
        return tp -> ResetElapsedSeconds();
    };
    
};

#endif
