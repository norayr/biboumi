#include <database/query.hpp>
#include <database/column.hpp>

void actual_bind(Statement& statement, const std::string& value, int index)
{
  statement.bind_text(index, value);
}

void actual_bind(Statement& statement, const std::int64_t& value, int index)
{
  statement.bind_int64(index, value);
}

void actual_bind(Statement& statement, const std::optional<bool>& value, int index)
{
  if (!value)
    statement.bind_int64(index, 0);
  else if (*value)
    statement.bind_int64(index, 1);
  else
    statement.bind_int64(index, -1);
}

void actual_add_param(Query& query, const std::string& val)
{
  query.params.push_back(val);
}

void actual_add_param(Query& query, const std::optional<bool>& val)
{
  if (!val)
    query.params.push_back("0");
  else if (*val)
    query.params.push_back("1");
  else
    query.params.push_back("-1");
}

Query& operator<<(Query& query, const char* str)
{
  query.body += str;
  return query;
}

Query& operator<<(Query& query, const std::string& str)
{
  query.body += "$" + std::to_string(query.current_param);
  query.current_param++;
  actual_add_param(query, str);
  return query;
}
