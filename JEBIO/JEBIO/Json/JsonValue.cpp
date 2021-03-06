#include "JsonValue.hpp"

#include <cassert>
#include <cmath>

namespace JEBIO { namespace Json {

JsonValue::JsonValue()
    : m_Type(Null)
{
    m_Value.integer = 0;
}

JsonValue::JsonValue(Type type)
    : m_Type(type)
{
    switch (type)
    {
    case Object:
        m_Value.object = new std::map<std::string, JsonValue>();
        break;
    case Array:
        m_Value.array = new std::vector<JsonValue>();
        break;
    case String:
        m_Value.string = new std::string();
        break;
    case Real:
        m_Value.real = 0;
        break;
    case Integer:
    case Null:
        m_Value.integer = 0;
        break;
    case Boolean:
        m_Value.boolean = false;
        break;
    }
}

JsonValue::JsonValue(const std::map<std::string, JsonValue>& object)
    : m_Type(Object)
{
    m_Value.object = new std::map<std::string, JsonValue>(object);
}

JsonValue::JsonValue(const std::vector<JsonValue>& array)
    : m_Type(Array)
{
    m_Value.array = new std::vector<JsonValue>(array);
}

JsonValue::JsonValue(const std::string& string)
    : m_Type(String)
{
    m_Value.string = new std::string(string);
}

JsonValue::JsonValue(const char* string)
    : m_Type(String)
{
    m_Value.string = new std::string(string);
}

JsonValue::JsonValue(double real)
    : m_Type(Real)
{
    m_Value.real = real;
}

JsonValue::JsonValue(int32_t integer)
    : m_Type(Integer)
{
    m_Value.integer = (int64_t)integer;
}

JsonValue::JsonValue(int64_t integer)
    : m_Type(Integer)
{
    m_Value.integer = (int64_t)integer;
}

JsonValue::JsonValue(uint32_t integer)
    : m_Type(Integer)
{
    m_Value.integer = (int64_t)integer;
}

JsonValue::JsonValue(uint64_t integer)
    : m_Type(Integer)
{
    m_Value.integer = (int64_t)integer;
}

JsonValue::JsonValue(bool boolean)
    : m_Type(Boolean)
{
    m_Value.boolean = boolean;
}

JsonValue::JsonValue(const JsonValue& rhs)
    : m_Type(rhs.m_Type)
{
    static_assert(sizeof(Value) == sizeof(int64_t), "JsonValue requires that doubles and pointers are 64-bit or less.");
    switch (m_Type)
    {
    case Object:
        m_Value.object = new JsonObject(rhs.object());
        break;
    case Array:
        m_Value.array = new JsonArray(rhs.array());
        break;
    case String:
        m_Value.string = new std::string(rhs.string());
        break;
    default:
        m_Value.integer = rhs.m_Value.integer;
        break;
    }
}

JsonValue::JsonValue(JsonValue&& rhs)
    : m_Type(rhs.m_Type)
{
    static_assert(sizeof(Value) == sizeof(int64_t), "JsonValue requires that doubles and pointers are 64-bit or less.");
    m_Value.integer = rhs.m_Value.integer;
    rhs.m_Type = Null;
    rhs.m_Value.object = nullptr;
}

JsonValue::~JsonValue()
{
    switch (m_Type)
    {
    case Object: delete m_Value.object; break;
    case Array: delete m_Value.array; break;
    case String: delete m_Value.string; break;
    default: break;
    }
}

JsonValue& JsonValue::operator=(const JsonValue& rhs)
{
    static_assert(sizeof(Value) == sizeof(int64_t), "JsonValue requires that doubles and pointers are 64-bit or less.");
    JsonValue copy(rhs); // Use copy constructor
    std::swap(m_Value.integer, copy.m_Value.integer);
    std::swap(m_Type, copy.m_Type);
    return *this; // Use move assignment operator
}

JsonValue& JsonValue::operator=(JsonValue&& rhs)
{
    static_assert(sizeof(Value) == sizeof(int64_t), "JsonValue requires that doubles and pointers are 64-bit or less.");
    m_Type = rhs.m_Type;
    m_Value.integer = rhs.m_Value.integer;
    rhs.m_Value.object = nullptr;
    rhs.m_Type = Null;
    return *this;
}

JsonValue::Type JsonValue::type() const
{
    return m_Type;
}

const std::map<std::string, JsonValue>& JsonValue::object() const
{
    if (m_Type != Object)
        throw JsonValueError("This JsonValue doesn't contain an object.");
    return *m_Value.object;
}

std::map<std::string, JsonValue>& JsonValue::object()
{
    if (m_Type != Object)
        throw JsonValueError("This JsonValue doesn't contain an object.");
    return *m_Value.object;
}

const std::vector<JsonValue>& JsonValue::array() const
{
    if (m_Type != Array)
        throw JsonValueError("This JsonValue doesn't contain an array.");
    return *m_Value.array;
}

std::vector<JsonValue>& JsonValue::array()
{
    if (m_Type != Array)
        throw JsonValueError("This JsonValue doesn't contain an array.");
    return *m_Value.array;
}

const std::string& JsonValue::string() const
{
    if (m_Type != String)
        throw JsonValueError("This JsonValue doesn't contain an string.");
    return *m_Value.string;
}

double JsonValue::real() const
{
    if (m_Type == Real)
        return m_Value.real;
    else if (m_Type == Integer)
        return (double)m_Value.integer;
    else
        throw JsonValueError("This JsonValue doesn't contain a real.");
}

int64_t JsonValue::integer() const
{
    if (m_Type == Integer)
    {
        return m_Value.integer;
    }
    else if (m_Type == Real)
    {
        double i;
        double f = std::modf(m_Value.real, &i);
        if (f == 0 && i >= (double)std::numeric_limits<int64_t>::min() &&
                i <= (double)std::numeric_limits<int64_t>::max())
            return (int64_t)i;
    }

    throw JsonValueError("This JsonValue doesn't contain an integer.");
}

bool JsonValue::boolean() const
{
    if (m_Type != Boolean)
        throw JsonValueError("This JsonValue doesn't contain a boolean.");
    return false;
}

}}
