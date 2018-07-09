#ifndef LIBCOLCORE_JSONUTILS_H
#define LIBCOLCORE_JSONUTILS_H

// Throws UnknownField() if _obj contains field names not listed in _allowedFields.
void validateFieldNames(json_spirit::mObject const& _obj, std::set<std::string> const& _allowedFields);

#endif //LIBCOLCORE_JSONUTILS_H
