#ifndef TEXTPROC_CXX
#define TEXTPROC_CXX

#include <new>

#ifndef TEXTPROC_HXX
#include <TextProc.hxx>
#endif

namespace TextProc
{
#line 284 "../../src/Com/Tokenizer.fog"
    CBase::CBase()
    :
        tokens(0),
        pos(0),
        ignore_newline(true)
    {};
    
#line 285
    CBase::CBase(Text::String str)
    :
        tokens(0),
        pos(0),
        ignore_newline(true)
    {
#line 285
        t.Create();
#line 285
        t -> Load(str, "cparser");
#line 285
        Load(t -> GetTokens());
    };
    
#line 286
    CBase::CBase(Text::String str, Text::String src_name)
    :
        tokens(0),
        pos(0),
        ignore_newline(true)
    {
#line 286
        t.Create();
#line 286
        t -> Load(str, src_name);
#line 286
        Load(t -> GetTokens());
    };
    
#line 287
    CBase::CBase(const Container::Vector < Token > & tokens)
    :
        tokens(0),
        pos(0),
        ignore_newline(true)
    {
#line 287
        Load(tokens);
    };
    
#line 929
    const Token& CBase::GetCurrent() const
    {
#line 930
        if (!tokens)
            throw InputExc("No token vector set");
        if (pos < 0 || pos >= tokens -> GetCount())
            throw InputExc("Invalid token position");
        return(*tokens)[pos];
    };
    
#line 945
    TextProc::FileLocation CBase::GetLocation() const
    {
#line 946
        return GetCurrent().loc;
    };
    
#line 304
    Pos CBase::GetPos()
    {
#line 304
        Pos p;
#line 304
        p.pos = pos;
#line 304
        return p;
    };
    
#line 301
    int CBase::GetTokenCount() const
    {
#line 301
        if (tokens)
#line 301
            return tokens -> GetCount();
        else
#line 301
            return 0;
    };
    
#line 975
    bool CBase::Id(Text::String id)
    {
#line 976
        const Token & tk = GetCurrent();
        if (tk.IsType(TK_ID) && tk.str_value == id)
        {
#line 978
            pos ++ ;
            return true;
        }
        return false;
    };
    
#line 937
    void CBase::IgnoreNewline(bool b)
    {
#line 938
        ignore_newline = b;
    };
    
    bool CBase::IsEnd() const
    {
#line 942
        return !tokens || pos >= tokens -> GetCount();
    };
    
#line 1002
    bool CBase::IsId() const
    {
#line 1003
        return GetCurrent().IsType(TK_ID);
    };
    
    bool CBase::IsInt() const
    {
#line 1007
        return GetCurrent().IsType(TK_INTEGER);
    };
    
    bool CBase::IsType(int i) const
    {
#line 1011
        return GetCurrent().IsType(i);
    };
    
#line 924
    void CBase::Load(const Container::Vector < Token > & tokens)
    {
#line 925
        this -> tokens = &tokens;
        pos = 0;
    };
    
#line 993
    bool CBase::Newline()
    {
#line 994
        const Token & tk = GetCurrent();
        if (tk.IsType(TK_NEWLINE))
        {
#line 996
            pos ++ ;
            return true;
        }
        return false;
    };
    
#line 315
    void CBase::PassId(Text::String s)
    {
#line 316
        if (IsType(TextProc::TK_ID) && GetCurrent().GetString() == s)
            Next();
        else
            throw InputExc((Text::String)"Expected id '" + s + "'");
    };
    
#line 968
    void CBase::PassNewline()
    {
#line 969
        const Token & tk = GetCurrent();
        if (tk.IsType(TK_NEWLINE))
            throw InputExc("Token is not newline");
        pos ++ ;
    };
    
#line 314
    void CBase::PassType(int i)
    {
#line 314
        if (!Type(i))
        {
#line 314
            throw InputExc((Text::String)"Expected type '" + Token::StaticGetTypeString(i) + "'");
        }
    };
    
#line 949
    Text::String CBase::ReadId()
    {
#line 950
        const Token & tk = GetCurrent();
        if (!tk.IsType(TK_ID))
            throw InputExc("Token is not id");
        pos ++ ;
        return tk.str_value;
    };
    
    int CBase::ReadInt()
    {
#line 958
        const Token & tk = GetCurrent();
        pos ++ ;
        if (tk.IsType(TextProc::TK_BIN))
#line 960
            return Text::String::BinInt(tk.str_value);
        if (tk.IsType(TextProc::TK_OCT))
#line 961
            return Text::String::OctInt(tk.str_value);
        if (tk.IsType(TextProc::TK_HEX))
#line 962
            return Text::String::HexInt(tk.str_value);
        if (tk.IsType(TextProc::TK_INTEGER))
#line 963
            return Text::String::StrInt(tk.str_value);
        pos -- ;
        throw InputExc("Token is not int");
    };
    
#line 305
    void CBase::SetPos(const Pos& p)
    {
        {
#line 305
            if (!(tokens && p.pos >= 0 && p.pos < tokens -> GetCount()))
            {
#line 305
                Lang::SysBreak("Assertion failed: tokens && p.pos >= 0 && p.pos < tokens->GetCount()");
            }
        }
#line 305
        ;
#line 305
        pos = p.pos;
    };
    
#line 984
    bool CBase::Type(int i)
    {
#line 985
        const Token & tk = GetCurrent();
        if (tk.IsType(i))
        {
#line 987
            pos ++ ;
            return true;
        }
        return false;
    };
    
#line 20 "../../src/Com/CompilerBase.fog"
    bool FileLocation::operator== (const FileLocation& t) const
    {
#line 8
        return Lang::Memory::Compare(this, &t, sizeof (FileLocation)) == 0;
    };
    
#line 8 "../../src/Com/JSON.fog"
    Interface::Value JSON::ParseArray(Tokenizer& tk)
    {
#line 9
        Interface::Value ret;
        Interface::ValueArray & arr = ret.CreateArray();
#line 12
        tk.PassToken('[');
#line 14
        while (!tk.IsToken(']'))
            {
                if (tk.IsToken(TextProc::TK_BRACKET_BEGIN))
                {
#line 17
                    arr.Add(ParseMap(tk));
                }
                else 
#line 19
                if (tk.IsToken(TextProc::TK_SQUARE_BEGIN))
                {
#line 20
                    arr.Add(ParseArray(tk));
                }
                else 
#line 22
                if (tk.IsToken(TextProc::TK_ID))
                {
#line 23
                    Text::String value = tk.ReadId();
                    if (value == "true")
                        arr.AddAsValue(true);
                    else 
#line 26
                    if (value == "false")
                        arr.AddAsValue(false);
                    else
                        arr.AddAsValue(value);
                }
                else 
#line 31
                if (tk.IsToken(TextProc::TK_INTEGER))
                {
#line 32
                    Lang::int64 value = tk.ReadInt();
                    arr.AddAsValue(value);
                }
                else 
#line 35
                if (tk.IsToken(TextProc::TK_FLOAT) || tk.IsToken(TextProc::TK_DOUBLE))
                {
#line 36
                    double value = tk.ReadDouble();
                    arr.AddAsValue(value);
                }
                else 
#line 39
                if (tk.IsToken(TextProc::TK_STRING))
                {
#line 40
                    Text::String value = tk.ReadString();
                    arr.AddAsValue(value);
                }
                else
                {
#line 44
                    throw Text::Exc("Unexpected token");
                }
#line 47
                tk.TryPassToken(TextProc::TK_COMMA);
            }
#line 50
        tk.PassToken(']');
#line 52
        return ret;
    };
    
#line 115
    Interface::Value JSON::ParseJSON(Text::String json)
    {
#line 116
        Interface::Value v;
#line 118
        Tokenizer tk;
        tk.SkipComments();
        tk.SkipNewLines();
        tk.SkipSeparateUnary();
#line 123
        if (!tk.Load(json, "json"))
        {
            {
#line 124
                Util::Log() << "Warning: Json tokenization failed" << "\n";
#line 124
                Util::Log().Flush();
            }
#line 125
            ;
#line 125
            for (int i = 0; i < tk.messages.GetCount(); i ++ )
                {
#line 126
                    ProcMsg & e = tk.messages[i];
                    {
#line 127
                        Util::Log() << "\t" << i << ": " << e.line << ":" << e.col << ": " << e.msg << "\n";
#line 127
                        Util::Log().Flush();
                    }
#line 128
                    ;
                }
        }
        try
        {
#line 132
            v = ParseMap(tk);
        }
        catch (Text::Exc e)
        {
#line 135
            tk.Dump();
            {
#line 136
                Util::Log() << "Error: Json parsing failed at " << tk.GetPassCursor() << ": " << e << "\n";
#line 136
                Util::Log().Flush();
            }
#line 137
            ;
        }
        return v;
    };
    
#line 55
    Interface::Value JSON::ParseMap(Tokenizer& tk)
    {
#line 56
        Interface::Value ret;
        Interface::ValueMap & vm = ret.CreateMap();
#line 59
        tk.PassToken(TextProc::TK_BRACKET_BEGIN);
#line 61
        while (!tk.IsToken(TextProc::TK_BRACKET_END))
            {
#line 62
                Text::String key;
                if (tk.IsToken(TextProc::TK_ID))
                    key = tk.ReadId();
                else
                    key = tk.ReadString();
#line 68
                if (tk.IsToken(TextProc::TK_COMMA) || tk.IsToken(TextProc::TK_BRACKET_END))
                {
#line 69
                    tk.TryPassToken(TextProc::TK_COMMA);
                    vm.Add(key);
                    continue;
                
                }
                tk.PassToken(TextProc::TK_COLON);
#line 76
                if (tk.IsToken(TextProc::TK_BRACKET_BEGIN))
                {
#line 77
                    vm.Add(key, ParseMap(tk));
                }
                else 
#line 79
                if (tk.IsToken(TextProc::TK_SQUARE_BEGIN))
                {
#line 80
                    vm.Add(key, ParseArray(tk));
                }
                else 
#line 82
                if (tk.IsToken(TextProc::TK_ID))
                {
#line 83
                    Text::String value = tk.ReadId();
                    if (value == "true")
                        vm.AddAsValue(key, true);
                    else 
#line 86
                    if (value == "false")
                        vm.AddAsValue(key, false);
                    else
                        vm.AddAsValue(key, value);
                }
                else 
#line 91
                if (tk.IsToken(TextProc::TK_INTEGER))
                {
#line 92
                    Lang::int64 value = tk.ReadInt();
                    vm.AddAsValue(key, value);
                }
                else 
#line 95
                if (tk.IsToken(TextProc::TK_FLOAT) || tk.IsToken(TextProc::TK_DOUBLE))
                {
#line 96
                    double value = tk.ReadDouble();
                    vm.AddAsValue(key, value);
                }
                else 
#line 99
                if (tk.IsToken(TextProc::TK_STRING))
                {
#line 100
                    Text::String value = tk.ReadString();
                    vm.AddAsValue(key, value);
                }
                else
                {
#line 104
                    throw Text::Exc("Unexpected token");
                }
#line 107
                tk.TryPassToken(TextProc::TK_COMMA);
            }
#line 110
        tk.PassToken(TextProc::TK_BRACKET_END);
#line 112
        return ret;
    };
    
#line 36 "../../src/Com/CompilerBase.fog"
    ProcMsg::ProcMsg(Text::String source, FileLocation loc, int severity, Text::String msg)
    :
        severity(0)
    {
#line 37
        src = source;
        SetFileLocation(loc);
        this -> severity = severity;
        this -> msg = msg;
    };
    
#line 35
    ProcMsg::ProcMsg(const ProcMsg& e)
    :
        severity(0)
    {
#line 35
        *this = e;
    };
    
#line 45
    void ProcMsg::operator= (const ProcMsg& e)
    {
#line 46
        msg = e.msg;
        file = e.file;
        src = e.src;
        line = e.line;
        col = e.col;
        severity = e.severity;
    };
    
#line 43
    bool ProcMsg::operator== (const ProcMsg& t) const
    {
#line 8
        return Lang::Memory::Compare(this, &t, sizeof (ProcMsg)) == 0;
    };
    
#line 61
    Text::String ProcMsg::AsString() const
    {
#line 62
        Text::String s;
        s << src << ": " << file << ":" << line << ":" << col << ": " << GetSeverityString() << ": " << msg;
#line 69
        return s;
    };
    
    Text::String ProcMsg::GetSeverityString() const
    {
#line 73
        switch (severity)
        {
#line 74
            case PROCMSG_SKIP:
#line 74
                return "skip";
            case PROCMSG_INFO:
#line 75
                return "info";
            case PROCMSG_WARNING:
#line 76
                return "warning";
            case PROCMSG_ERROR:
#line 77
                return "error";
            default:
#line 78
                return "<invalid severity>";
        }
    };
    
#line 54
    void ProcMsg::Set(Text::String source, FileLocation loc, int severity, Text::String msg)
    {
#line 55
        this -> src = source;
        SetFileLocation(loc);
        this -> severity = severity;
        this -> msg = msg;
    };
    
#line 104 "../../src/Com/Tokenizer.fog"
    Token::Token()
    :
        type(0),
        spaces(0)
    {};
    
#line 105
    Token::Token(const Token& t)
    :
        type(0),
        spaces(0)
    {
#line 105
        *this = t;
    };
    
#line 106
    void Token::operator= (const Token& t)
    {
#line 106
        type = t.type;
#line 106
        str_value = t.str_value;
#line 106
        loc = t.loc;
#line 106
        end = t.end;
#line 106
        spaces = t.spaces;
    };
    
#line 107
    bool Token::operator== (const Token& t) const
    {
#line 107
        return t.type == type && t.str_value == str_value && t.loc == loc && end == t.end && t.spaces == spaces;
    };
    
#line 159
    Text::String Token::AsString() const
    {
#line 160
        Text::String s = GetTypeString() + ": " + Text::EscapeString(GetTextValue());
        return s;
    };
    
    Text::String Token::StaticGetTextValue(int type, Text::String str_value)
    {
#line 165
        switch (type)
        {
#line 166
            case TK_UNKNOWN:
#line 166
                return "";
            case TK_ID:
#line 167
                return str_value;
            case TK_INTEGER:
#line 168
                return str_value;
            case TK_FLOAT:
#line 169
                return str_value;
            case TK_DOUBLE:
#line 170
                return str_value;
            case TK_EXCLAMATION:
#line 171
                return "!";
            case TK_STRING:
#line 172
                return(Text::String)"\"" + Text::EscapeString(str_value) + "\"";
            case TK_NUMBERSIGN:
#line 173
                return "#";
            case TK_PERCENT:
#line 174
                return "%";
            case TK_AMPERSAND:
#line 175
                return "&";
            case TK_BRACKET_BEGIN:
#line 176
                return "{";
            case TK_BRACKET_END:
#line 177
                return "}";
            case TK_DIV:
#line 178
                return "/";
            case TK_PARENTHESIS_BEGIN:
#line 179
                return "(";
            case TK_PARENTHESIS_END:
#line 180
                return ")";
            case TK_SQUARE_BEGIN:
#line 181
                return "[";
            case TK_SQUARE_END:
#line 182
                return "]";
            case TK_ASS:
#line 183
                return "=";
            case TK_QUESTION:
#line 184
                return "\?";
            case TK_PLUS:
#line 185
                return "+";
            case TK_SOLIDUS:
#line 186
                return "\\";
            case TK_ACCENT:
#line 187
                return "^";
            case TK_TILDE:
#line 188
                return "~";
            case TK_MUL:
#line 189
                return "*";
            case TK_CHAR:
#line 190
                return(Text::String)"'" + Text::EscapeString(str_value) + "'";
            case TK_OR:
#line 191
                return "|";
            case TK_MINUS:
#line 192
                return "-";
            case TK_SEMICOLON:
#line 193
                return ";";
            case TK_COMMA:
#line 194
                return ",";
            case TK_PUNCT:
#line 195
                return ".";
            case TK_COLON:
#line 196
                return ":";
            case TK_LESS:
#line 197
                return "<";
            case TK_GREATER:
#line 198
                return ">";
            case TK_NEWLINE:
#line 199
                return "\n";
            case TK_BLOCK_COMMENT:
#line 200
                return(Text::String)"/* " + str_value + "*/";
            case TK_COMMENT:
#line 201
                return(Text::String)"// " + str_value;
            case TK_BIN:
#line 202
                return str_value;
            case TK_HEX:
#line 203
                return str_value;
            case TK_OCT:
#line 204
                return str_value;
            case TK_DOLLARSIGN:
#line 205
                return "$";
            case TK_3DOTS:
#line 206
                return "...";
            case TK_EOF:
#line 207
                return "EOF";
            default:
#line 208
                Util::Panic("Unhandled token type");
        }
        return "";
    };
    
#line 112
    Text::String Token::StaticGetTypeString(int type)
    {
#line 113
        switch (type)
        {
#line 114
            case TK_UNKNOWN:
#line 114
                return "<unknown>";
            case TK_ID:
#line 115
                return "id";
            case TK_INTEGER:
#line 116
                return "integer";
            case TK_FLOAT:
#line 117
                return "float";
            case TK_DOUBLE:
#line 118
                return "double";
            case TK_EXCLAMATION:
#line 119
                return "exclamation";
            case TK_STRING:
#line 120
                return "string";
            case TK_NUMBERSIGN:
#line 121
                return "number-sign";
            case TK_PERCENT:
#line 122
                return "percent";
            case TK_AMPERSAND:
#line 123
                return "ampersand";
            case TK_DIV:
#line 124
                return "divide";
            case TK_BRACKET_BEGIN:
#line 125
                return "bracket-begin";
            case TK_BRACKET_END:
#line 126
                return "bracket-end";
            case TK_PARENTHESIS_BEGIN:
#line 127
                return "parenthesis-begin";
            case TK_PARENTHESIS_END:
#line 128
                return "parenthesis-end";
            case TK_SQUARE_BEGIN:
#line 129
                return "square-begin";
            case TK_SQUARE_END:
#line 130
                return "square-end";
            case TK_ASS:
#line 131
                return "assign";
            case TK_QUESTION:
#line 132
                return "question-mark";
            case TK_PLUS:
#line 133
                return "plus";
            case TK_SOLIDUS:
#line 134
                return "solidus";
            case TK_ACCENT:
#line 135
                return "accent";
            case TK_TILDE:
#line 136
                return "tilde";
            case TK_MUL:
#line 137
                return "multiply";
            case TK_CHAR:
#line 138
                return "char";
            case TK_OR:
#line 139
                return "or";
            case TK_MINUS:
#line 140
                return "minus";
            case TK_SEMICOLON:
#line 141
                return "semicolon";
            case TK_COMMA:
#line 142
                return "comma";
            case TK_PUNCT:
#line 143
                return "punct";
            case TK_COLON:
#line 144
                return "colon";
            case TK_LESS:
#line 145
                return "less";
            case TK_GREATER:
#line 146
                return "greater";
            case TK_NEWLINE:
#line 147
                return "newline";
            case TK_BLOCK_COMMENT:
#line 148
                return "block-comment";
            case TK_COMMENT:
#line 149
                return "comment";
            case TK_BIN:
#line 150
                return "binary-number";
            case TK_HEX:
#line 151
                return "hex-number";
            case TK_OCT:
#line 152
                return "oct-number";
            case TK_INVALID:
#line 153
                return "invalid";
            case TK_3DOTS:
#line 154
                return "3-dots";
            case TK_EOF:
#line 155
                return "end-of-file";
        }
        return "";
    };
    
#line 347
    Tokenizer::Tokenizer()
    :
        cursor(0),
        skip_comments(false),
        skip_newlines(false),
        skip_separateunary(false),
        pass_cursor(0),
        tab_size(4)
    {};
    
#line 351
    Token& Tokenizer::Add(int token_id)
    {
#line 352
        struct Token & t = tokens.Add();
        t.loc = loc;
        t.end = loc;
        t.end.col ++ ;
        t.type = token_id;
        return t;
    };
    
#line 234
    void Tokenizer::AddError(TextProc::FileLocation loc, Text::String msg)
    {
#line 234
        messages.Add().Set("Tokenizer", loc, PROCMSG_ERROR, msg);
    };
    
#line 235
    void Tokenizer::AddWarning(TextProc::FileLocation loc, Text::String msg)
    {
#line 235
        messages.Add().Set("Tokenizer", loc, PROCMSG_WARNING, msg);
    };
    
#line 852
    void Tokenizer::AppendString(Text::String& s)
    {
#line 853
        int chr = input[cursor];
        if (chr == '\\')
        {
#line 855
            int chr1;
            if (cursor + 1 < input.GetCount())
#line 856
                chr1 = input[cursor + 1];
            else
#line 857
                chr1 = 0;
            if (chr1 == '\'')
            {
#line 859
                Next();
#line 859
                Next();
                s.Cat(0x27);
            }
            else 
#line 862
            if (chr1 == '"')
            {
#line 863
                Next();
#line 863
                Next();
                s.Cat(0x22);
            }
            else 
#line 866
            if (chr1 == '\?')
            {
#line 867
                Next();
#line 867
                Next();
                s.Cat(0x3F);
            }
            else 
#line 870
            if (chr1 == '\\')
            {
#line 871
                Next();
#line 871
                Next();
                s.Cat(0x5c);
            }
            else 
#line 874
            if (chr1 == 'a')
            {
#line 875
                Next();
#line 875
                Next();
                s.Cat(0x07);
            }
            else 
#line 878
            if (chr1 == 'b')
            {
#line 879
                Next();
#line 879
                Next();
                s.Cat(0x08);
            }
            else 
#line 882
            if (chr1 == 'f')
            {
#line 883
                Next();
#line 883
                Next();
                s.Cat(0x0c);
            }
            else 
#line 886
            if (chr1 == 'n')
            {
#line 887
                Next();
#line 887
                Next();
                s.Cat(0x0a);
            }
            else 
#line 890
            if (chr1 == 'r')
            {
#line 891
                Next();
#line 891
                Next();
                s.Cat(0x0d);
            }
            else 
#line 894
            if (chr1 == 't')
            {
#line 895
                Next();
#line 895
                Next();
                s.Cat(0x09);
            }
            else 
#line 898
            if (chr1 == 'v')
            {
#line 899
                Next();
#line 899
                Next();
                s.Cat(0x0b);
            }
            else
            {
#line 903
                s.Cat(chr);
                Next();
            }
        }
        else
        {
#line 908
            s.Cat(chr);
            Next();
        }
    };
    
#line 245
    void Tokenizer::Dump() const
    {
        {
            {
#line 245
                Util::Log() << "tokens" << " {" << "\n";
#line 245
                Util::Log().Flush();
            }
#line 245
            ;
#line 245
            for (int i = 0; i < tokens.GetCount(); i ++ )
                {
#line 245
                    Util::Log() << "\t[" << i << "]: " << Text::ToString(tokens[i]) << "\n";
#line 245
                    Util::Log().Flush();
                }
#line 245
            ;
            {
#line 245
                Util::Log() << "}" << "\n";
#line 245
                Util::Log().Flush();
            }
#line 245
            ;
        }
#line 245
        ;
    };
    
#line 371
    bool Tokenizer::IsToken(int tk)
    {
#line 372
        if (pass_cursor >= tokens.GetCount())
#line 372
            return false;
        return tokens[pass_cursor].type == tk;
    };
    
#line 402
    bool Tokenizer::Load(Text::String str, Text::String path)
    {
#line 403
        input = str;
#line 405
        loc.file = path;
        loc.line = 1;
        loc.col = 1;
#line 409
        cursor = 0;
#line 411
        while (cursor < input.GetCount())
            {
#line 412
                int chr = input[cursor];
#line 414
                if (Text::IsAlpha(chr) || chr == '_')
                {
#line 415
                    Token & t = Add(TK_ID);
                    t.str_value.Cat(chr);
                    Next();
                    while (cursor < input.GetCount())
                        {
#line 419
                            int chr = input[cursor];
                            if (Text::IsAlpha(chr) || chr == '_' || Text::IsDigit(chr))
                            {
#line 421
                                t.str_value.Cat(chr);
                                Next();
                            }
                            else
                                break;
                        
                        }
#line 427
                    t.end = loc;
                }
                else 
#line 429
                if (Text::IsDigit(chr))
                {
#line 430
                    Text::String n;
                    if (skip_separateunary && tokens.GetCount())
                    {
#line 432
                        while (tokens.GetCount() && tokens.Top().IsType(TK_MINUS))
                            {
#line 433
                                tokens.Pop();
                                n.Cat('-');
                            }
                        while (tokens.GetCount() && tokens.Top().IsType(TK_PLUS))
                            {
#line 437
                                tokens.Pop();
                            }
                    }
                    Token & tk = Add(TK_INTEGER);
                    bool is_double = false;
#line 441
                    bool is_float = false;
                    n.Cat(chr);
                    Next();
                    int exp;
                    if (chr == '0')
#line 445
                        exp = FP_OCTHEX;
                    else
#line 446
                        exp = FP_INT;
                    while (cursor < input.GetCount())
                        {
#line 448
                            int chr = input[cursor];
                            bool cat = false;
#line 451
                            if (exp == FP_INT)
                            {
#line 452
                                if (Text::IsDigit(chr))
                                    cat = true;
                                else 
#line 454
                                if (chr == '.')
                                {
#line 455
                                    exp = FP_FRAC;
                                    cat = true;
                                    is_double = true;
                                }
                                else 
#line 459
                                if (chr == 'e' || chr == 'E')
                                {
#line 460
                                    exp = FP_SIGN;
                                    cat = true;
                                    is_double = true;
                                }
                            }
                            else 
#line 465
                            if (exp == FP_FRAC)
                            {
#line 466
                                if (Text::IsDigit(chr))
                                    cat = true;
                                else 
#line 468
                                if (chr == 'e' || chr == 'E')
                                {
#line 469
                                    exp = FP_SIGN;
                                    cat = true;
                                    is_double = true;
                                }
                            }
                            else 
#line 474
                            if (exp == FP_SIGN)
                            {
#line 475
                                if (chr == '+' || chr == '-' || Text::IsDigit(chr))
                                {
#line 476
                                    exp = FP_EXP;
                                    cat = true;
                                }
                                else 
#line 479
                                if (chr == 'f' || chr == 'F')
                                {
#line 480
                                    exp = FP_END;
                                    cat = true;
                                    is_float = true;
                                }
                            }
                            else 
#line 485
                            if (exp == FP_EXP)
                            {
#line 486
                                if (Text::IsDigit(chr))
                                    cat = true;
                                else 
#line 488
                                if (chr == 'f' || chr == 'F')
                                {
#line 489
                                    exp = FP_END;
                                    cat = true;
                                    is_float = true;
                                }
                            }
                            else 
#line 494
                            if (exp == FP_OCTHEX)
                            {
#line 495
                                if (chr == 'b' || chr == 'B')
                                {
#line 496
                                    exp = FP_BIN;
                                    cat = true;
                                }
                                else 
#line 499
                                if (chr == 'x' || chr == 'X')
                                {
#line 500
                                    exp = FP_HEX;
                                    cat = true;
                                }
                                else 
#line 503
                                if (chr >= '0' && chr <= '7')
                                {
#line 504
                                    exp = FP_OCT;
                                    cat = true;
                                }
                                else 
#line 507
                                if (chr == '.')
                                {
#line 508
                                    exp = FP_FRAC;
                                    cat = true;
                                    is_double = true;
                                }
                            }
                            else 
#line 513
                            if (exp == FP_HEX)
                            {
#line 514
                                if ((chr >= '0' && chr <= '9') || (chr >= 'a' && chr <= 'f') || (chr >= 'A' && chr <= 'F'))
                                {
#line 517
                                    cat = true;
                                }
                            }
                            else 
#line 520
                            if (exp == FP_OCT)
                            {
#line 521
                                if (chr >= '0' && chr <= '7')
                                {
#line 522
                                    cat = true;
                                }
                            }
#line 526
                            if (cat)
                            {
#line 527
                                Next();
                                n.Cat(chr);
                                if (exp == FP_END)
#line 529
                                    break;
                            
                            }
                            else
#line 531
                                break;
                        
                        }
                    tk.str_value = n;
#line 536
                    if (exp == FP_BIN)
#line 536
                        tk.type = TK_BIN;
                    else 
#line 537
                    if (exp == FP_HEX)
#line 537
                        tk.type = TK_HEX;
                    else 
#line 538
                    if (exp == FP_OCT)
#line 538
                        tk.type = TK_OCT;
                    else 
#line 539
                    if (is_double)
                    {
#line 540
                        if (!is_float)
                            tk.type = TK_DOUBLE;
                        else
                            tk.type = TK_FLOAT;
                    }
#line 546
                    tk.end = loc;
                }
                else 
#line 548
                if (chr == '!')
                {
#line 549
                    Token & tk = Add(TK_EXCLAMATION);
                    Next();
                    tk.end = loc;
                }
                else 
#line 553
                if (chr == '"')
                {
#line 554
                    Token & tk = Add(TK_STRING);
                    int begin_line = loc.line;
                    int begin_col = loc.col;
                    Next();
                    Text::String str;
                    bool success = false;
                    while (cursor < input.GetCount())
                        {
#line 561
                            int chr = input[cursor];
                            Text::String tmp;
                            tmp.Cat(chr);
                            if (chr == '\n')
                            {
#line 565
                                AddError(tk.loc, "no newline allowed in string literal");
                                Next();
                                loc.line ++ ;
                                loc.col = 1;
                            }
                            else 
#line 570
                            if (chr == '"')
                            {
#line 571
                                Next();
                                success = true;
                                break;
                            
                            }
                            else 
#line 575
                            if (chr == '\\')
                            {
#line 576
                                AppendString(str);
                            }
                            else
                            {
#line 579
                                str.Cat(chr);
                                Next();
                            }
                        }
                    tk.end = loc;
#line 585
                    if (success)
                    {
#line 586
                        tk.str_value = str;
                    }
                    else
                    {
#line 589
                        AddError(tk.loc, "no finishing \" in string literal");
                        return false;
                    }
                }
                else 
#line 593
                if (chr == '#')
                {
#line 594
                    Token & tk = Add(TK_NUMBERSIGN);
                    Next();
                    tk.end = loc;
                }
                else 
#line 598
                if (chr == '%')
                {
#line 599
                    Token & tk = Add(TK_PERCENT);
                    Next();
                    tk.end = loc;
                }
                else 
#line 603
                if (chr == '&')
                {
#line 604
                    Token & tk = Add(TK_AMPERSAND);
                    Next();
                    tk.end = loc;
                }
                else 
#line 608
                if (chr == '/')
                {
#line 609
                    int begin_line = loc.line;
                    int begin_col = loc.col;
                    int chr1;
                    if (cursor + 1 < input.GetCount())
#line 612
                        chr1 = input[cursor + 1];
                    else
#line 613
                        chr1 = 0;
                    if (chr1 == '*')
                    {
#line 615
                        Token * tk = 0;
                        if (!skip_comments)
                            tk = &Add(TK_BLOCK_COMMENT);
                        Next();
                        Next();
                        Text::String c;
                        bool succ = false;
                        while (cursor < input.GetCount())
                            {
#line 623
                                chr = input[cursor];
                                if (chr == '*')
                                {
#line 625
                                    if (cursor + 1 < input.GetCount())
#line 625
                                        chr1 = input[cursor + 1];
                                    else
#line 626
                                        chr1 = 0;
                                    if (chr1 == '/')
                                    {
#line 628
                                        Next();
                                        Next();
                                        if (tk)
#line 630
                                            tk -> str_value = c;
                                        succ = true;
                                        break;
                                    
                                    }
                                    else
#line 634
                                        c.Cat(chr);
                                }
                                else
#line 636
                                    c.Cat(chr);
                                Next();
                            }
                        if (tk)
                        {
#line 640
                            tk -> end = loc;
                            if (!succ)
                                AddError(tk -> loc, "unterminated /* comment");
                        }
                    }
                    else 
#line 645
                    if (chr1 == '/')
                    {
#line 646
                        Token * tk = 0;
                        if (!skip_comments)
                            tk = &Add(TK_COMMENT);
                        Next();
                        Next();
                        Text::String c;
                        while (cursor < input.GetCount())
                            {
#line 653
                                chr = input[cursor];
                                if (chr == '\n')
                                {
#line 655
                                    if (tk)
#line 655
                                        tk -> str_value = c;
                                    break;
                                
                                }
                                else
#line 658
                                    c.Cat(chr);
                                Next();
                            }
                        if (tk)
#line 661
                            tk -> end = loc;
                    }
                    else
                    {
#line 664
                        Token & tk = Add(TK_DIV);
                        Next();
                        tk.end = loc;
                    }
                }
                else 
#line 669
                if (chr == '{')
                {
#line 670
                    Add(TK_BRACKET_BEGIN);
                    Next();
                }
                else 
#line 673
                if (chr == '}')
                {
#line 674
                    Add(TK_BRACKET_END);
                    Next();
                }
                else 
#line 677
                if (chr == '(')
                {
#line 678
                    Add(TK_PARENTHESIS_BEGIN);
                    Next();
                }
                else 
#line 681
                if (chr == ')')
                {
#line 682
                    Add(TK_PARENTHESIS_END);
                    Next();
                }
                else 
#line 685
                if (chr == '[')
                {
#line 686
                    Add(TK_SQUARE_BEGIN);
                    Next();
                }
                else 
#line 689
                if (chr == ']')
                {
#line 690
                    Add(TK_SQUARE_END);
                    Next();
                }
                else 
#line 693
                if (chr == '=')
                {
#line 694
                    Add(TK_ASS);
                    Next();
                }
                else 
#line 697
                if (chr == '+')
                {
#line 698
                    Add(TK_PLUS);
                    Next();
                }
                else 
#line 701
                if (chr == '\?')
                {
#line 702
                    Add(TK_QUESTION);
                    Next();
                }
                else 
#line 705
                if (chr == '\\')
                {
#line 706
                    Add(TK_SOLIDUS);
                    Next();
                }
                else 
#line 709
                if (chr == '^')
                {
#line 710
                    Add(TK_ACCENT);
                    Next();
                }
                else 
#line 713
                if (chr == '~')
                {
#line 714
                    Add(TK_TILDE);
                    Next();
                }
                else 
#line 717
                if (chr == '*')
                {
#line 718
                    Add(TK_MUL);
                    Next();
                }
                else 
#line 721
                if (chr == '@')
                {
#line 722
                    Add(TK_AT);
                    Next();
                }
                else 
#line 725
                if (chr == '\'')
                {
#line 726
                    Token & tk = Add(TK_CHAR);
                    Next();
                    Text::String str;
                    bool success = false;
                    while (cursor < input.GetCount())
                        {
#line 731
                            int chr = input[cursor];
                            if (chr == '\n')
                            {
#line 733
                                AddError(tk.loc, "no newline allowed in char literal");
                                Next();
                                loc.line ++ ;
                                loc.col = 1;
                            }
                            else 
#line 738
                            if (chr == '\'')
                            {
#line 739
                                Next();
                                success = true;
                                break;
                            
                            }
                            else 
#line 743
                            if (chr == '\\')
                            {
#line 744
                                AppendString(str);
                            }
                            else
                            {
#line 747
                                str.Cat(chr);
                                Next();
                            }
                        }
                    tk.end = loc;
#line 753
                    if (success)
                    {
#line 754
                        tk.str_value = str;
                    }
                    else
                    {
#line 757
                        AddError(tk.loc, "no finishing ' in char literal");
                        return false;
                    }
                }
                else 
#line 761
                if (chr == '-')
                {
#line 762
                    Add(TK_MINUS);
                    Next();
                }
                else 
#line 765
                if (chr == ';')
                {
#line 766
                    Add(TK_SEMICOLON);
                    Next();
                }
                else 
#line 769
                if (chr == ',')
                {
#line 770
                    Add(TK_COMMA);
                    Next();
                }
                else 
#line 773
                if (chr == '.')
                {
#line 774
                    if (cursor + 2 < input.GetCount() && input[cursor + 1] == '.' && input[cursor + 2] == '.')
                    {
#line 775
                        Add(TK_3DOTS);
                        Next();
                        Next();
                        Next();
                    }
                    else
                    {
#line 781
                        Add(TK_PUNCT);
                        Next();
                    }
                }
                else 
#line 785
                if (chr == ':')
                {
#line 786
                    Add(TK_COLON);
                    Next();
                }
                else 
#line 789
                if (chr == '<')
                {
#line 790
                    Add(TK_LESS);
                    Next();
                }
                else 
#line 793
                if (chr == '>')
                {
#line 794
                    Add(TK_GREATER);
                    Next();
                }
                else 
#line 797
                if (chr == '|')
                {
#line 798
                    Add(TK_OR);
                    Next();
                }
                else 
#line 801
                if (chr == '\n')
                {
#line 802
                    if (!skip_newlines)
                    {
#line 803
                        Token & tk = Add(TK_NEWLINE);
                        tk.end.col = 1;
#line 804
                        tk.end.line ++ ;
                    }
                    Next();
                    loc.line ++ ;
                    loc.col = 1;
                }
                else 
#line 810
                if (chr == '\t')
                {
#line 811
                    if (!tokens.IsEmpty())
                        tokens.Top().spaces += tab_size;
                    Next();
                    loc.col += tab_size - 1;
                }
                else 
#line 816
                if (Text::IsSpace(chr))
                {
#line 817
                    if (!tokens.IsEmpty())
                        tokens.Top().spaces ++ ;
                    Next();
                }
                else 
#line 821
                if (chr == 0)
                    break;
                
                else
                {
#line 824
                    Lang::byte b = chr;
                    if (b >= 0x80 && b <= 0xFF)
                    {
#line 826
                        Next();
                        while (cursor < input.GetCount())
                            {
#line 828
                                b = input[cursor];
                                if (b >= 0x80 && b <= 0xFF)
                                    cursor ++ ;
                                else
                                    break;
                            
                            }
                        if (!tokens.IsEmpty())
                            tokens.Top().spaces ++ ;
                    }
                    else
                    {
#line 839
                        Text::String msg = "unexpected character '";
                        msg.Cat(chr);
                        msg.Cat('\'');
                        AddError(loc, msg);
                        Next();
                    }
                }
            }
        Add(TK_EOF);
#line 849
        return messages.IsEmpty();
    };
    
#line 366
    void Tokenizer::PassToken(int tk)
    {
#line 367
        if (!IsToken(tk))
#line 367
            throw InputExc("Unexpected token");
        pass_cursor ++ ;
    };
    
#line 397
    double Tokenizer::ReadDouble()
    {
#line 398
        if (!IsToken(TK_DOUBLE) && !IsToken(TK_FLOAT))
#line 398
            throw InputExc("Unexpected token");
        return Text::String::StrDbl(tokens[pass_cursor ++ ].str_value);
    };
    
#line 387
    Text::String Tokenizer::ReadId()
    {
#line 388
        if (!IsToken(TK_ID))
#line 388
            throw InputExc("Unexpected token");
        return tokens[pass_cursor ++ ].str_value;
    };
    
    Lang::int64 Tokenizer::ReadInt()
    {
#line 393
        if (!IsToken(TK_INTEGER))
#line 393
            throw InputExc("Unexpected token");
        return Text::String::StrInt64(tokens[pass_cursor ++ ].str_value);
    };
    
#line 382
    Text::String Tokenizer::ReadString()
    {
#line 383
        if (!IsToken(TK_STRING))
#line 383
            throw InputExc("Unexpected token");
        return tokens[pass_cursor ++ ].str_value;
    };
    
#line 376
    bool Tokenizer::TryPassToken(int tk)
    {
#line 377
        if (!IsToken(tk))
#line 377
            return false;
        pass_cursor ++ ;
        return true;
    };
    
};

#endif
