//
// Implement extended string methods such as split, join, etc.
//

#pragma once

#include <tchar.h>

#include <stdexcept>
#include <string>
#include <vector>
#include <memory>

namespace Extensions
{
    namespace Strings
    {
        //
        // Extend the standard string class by providing useful methods on
        // a string and collections of strings.
        //
        // T is a string class (std::string, std::wstring).
        // Container is a class that supports push_back.
        //

        template<class T, typename Container = std::vector<T>>
        class StringExtensionsT
        {
        public:

            typedef Container container_type;
            typedef T string_type;

            //
            // Constructor.  Hold a reference to our content string.
            //

            StringExtensionsT(const T & contents)
                : m_contents(contents)
            {
            }

            //
            // Destructor.
            //

            ~StringExtensionsT()
            {
            }

            //
            // Return a const reference to our contents.
            //

            const T & Contents() const
            {
                return m_contents;
            }

            //
            // Split a string into a collection of substrings delimited by
            // any of a set of delimiters.  Return the collection of the items
            // to the caller.
            //

            std::unique_ptr<Container> Split(const T & separators) const
            {
                auto results = std::make_unique<Container>();
                size_t sepPosition;
                size_t currentPosition;

                //
                // If the separators are null, return the contents.
                //

                if (separators.length() == 0)
                {
                    results->push_back(m_contents);
                }
                else
                {
                    //
                    // If there aren't any separators in the string, return
                    // the entire string.
                    //

                    sepPosition = m_contents.find_first_of(separators);

                    //
                    // Copy each substring from the current position to
                    // before the split to the output list.
                    //

                    currentPosition = 0;
                    while (sepPosition != T::npos)
                    {
                        results->push_back(
                                    m_contents.substr(
                                        currentPosition,
                                        sepPosition - currentPosition));

                        currentPosition = sepPosition + 1;

                        //
                        // Find the next separator.
                        //

                        sepPosition = m_contents.find_first_of(separators, currentPosition);
                    }

                    //
                    // Copy the tail of the last split.  This is the
                    // string from the current position to the end.
                    //

                    results->push_back(m_contents.substr(currentPosition));
                }

                return results;
            }

            //
            // Default separator is a space.
            //

            std::unique_ptr<Container> Split() const
            {
                static const T separator(" ");

                return Split(separator);
            }

            //
            // Split the string, removing empty strings.
            //

            std::unique_ptr<Container> Split(const T & separators, bool removeEmpty) const
            {
                //
                // Split the string, then if a string is empty, remove it from
                // the container.
                //

                auto results = Split(separators);
                RemoveEmptyStrings(*results);

                return results;
            }

            //
            // Split the string, using only " " as a separator and remove
            // empty strings.
            //

            std::unique_ptr<Container> Split(bool removeEmpty) const
            {
                //
                // Split the string, then if a string is empty, remove it from
                // the container.
                //

                auto results = Split();
                RemoveEmptyStrings(*results);

                return results;
            }

            //
            // Trim spaces from the left side of the string.  Return a new
            // StringExtension instance.  The default characters to use
            // for trimming are space, tab, new line, formfeed and return.
            //

            template<class ContainerType = Container>
            std::unique_ptr<StringExtensionsT<T, ContainerType>> TrimStart() const
            {
                return TrimStart<ContainerType>(T(" \t\n\r\f"));
            }

            //
            // Trim any of a set of characters and return a new StringExtension.
            // If m_contents consists of ONLY stripChars, then an empty
            // string is used.
            //

            template<typename ContainerType = Container>
            std::unique_ptr<StringExtensionsT<T, ContainerType>> TrimStart(const T & stripChars) const
            {
                size_t firstPos;
                T newString;

                //
                // Find the first character that is not a character to strip.
                //

                firstPos = m_contents.find_first_not_of(stripChars);
                if (firstPos != T::npos)
                {
                    //
                    // A character was found that was not in stripChars.
                    // Extract from that position to the end of the string.
                    //

                    newString = m_contents.substr(firstPos);
                }

                return std::make_unique<StringExtensionsT<T, ContainerType>>(newString);
            }

            //
            // Trim spaces from the right side of the string.  Return a new
            // StringExtension instance.  The default characters to use
            // for trimming are space, tab, new line, formfeed and return.
            //

            template<class ContainerType = Container>
            std::unique_ptr<StringExtensionsT<T, ContainerType>> TrimEnd() const
            {
                return TrimEnd<ContainerType>(T(" \t\n\r\f"));
            }

            //
            // Trim any of a set of characters and return a new StringExtension.
            // If m_contents consists of ONLY stripChars, then an empty
            // string is used.
            //

            template<typename ContainerType = Container>
            std::unique_ptr<StringExtensionsT<T, ContainerType>> TrimEnd(const T & stripChars) const
            {
                size_t lastPos;
                T newString;

                //
                // Find the last character that is not a character to strip.
                //

                lastPos = m_contents.find_last_not_of(stripChars);
                if (lastPos != T::npos)
                {
                    //
                    // A character was found that was not in stripChars.
                    // Extract from the start to that position.
                    //

                    newString = m_contents.substr(0, lastPos + 1);
                }

                return std::make_unique<StringExtensionsT<T, ContainerType>>(newString);
            }

            //
            // Trim space from both the right and left ends of a string.
            //

            template<class ContainerType = Container>
            std::unique_ptr<StringExtensionsT<T, ContainerType>> Trim() const
            {
                return Trim<ContainerType>(T(" \t\n\r\f"));
            }

            //
            // Trim any of a set of characters and return a new StringExtension.
            // If m_contents consists of ONLY stripChars, then an empty
            // string is used.
            //

            template<typename ContainerType = Container>
            std::unique_ptr<StringExtensionsT<T, ContainerType>> Trim(const T & stripChars) const
            {
                //
                // Trim the start first.  If the returned string is empty,
                // return it.  Otherwise, trim the end.
                //

                auto newExtension = TrimStart(stripChars);
                if (newExtension->Contents().length() == 0)
                {
                    return newExtension;
                }

                return newExtension->TrimEnd(stripChars);
            }

        private:

            //
            // Remove empty strings from a container.
            //

            void RemoveEmptyStrings(Container & container) const
            {
                Container::iterator it;
                static T emptyString;
                Container newContainer;

                //
                // Remove empty strings from the container.
                //

                for (it = container.begin(); it != container.end(); ++it)
                {
                    if (*it != emptyString)
                    {
                        newContainer.push_back(*it);
                    }
                }

                //
                // If there were erased items, then copy the container
                // without the empty strings to the original container.
                //

                if (newContainer.size() != container.size())
                {
                    container = newContainer;
                }
            }

            //
            // String manipulated by this class.
            //

            T m_contents;
        };

        //
        // Create an alias to the StringExtensions template on std::string using the default
        // container.
        //

        using StringExtensions = StringExtensionsT<std::string>;

        //
        // Convert a std::string to a long.  Return true if the string was
        // successfully converted and false otherwise.
        //

        template <class T, typename U>
        bool FromString(const T & value, U * result)
        {
            T::size_type sz;
            U convertedvalue;

            //
            // Fail if there is no output pointer.
            //

            if (!result)
            {
                return false;
            }

            //
            // Trim any characters from the string before converting it.
            //

            std::unique_ptr<StringExtensionsT<T>> se = std::make_unique<StringExtensionsT<T>>(value);
            auto trimmed(se->Trim());

            try
            {
                convertedvalue = (U) std::stoll(trimmed->Contents(), &sz);
                if (trimmed->Contents()[sz] != 0)
                {
                    //
                    // Expect terminating character to be a null.
                    //

                    return false;
                }

                //
                // Set the output value.
                //

                *result = convertedvalue;
            }
            catch (std::invalid_argument &)
            {
                return false;
            }
            catch (std::out_of_range &)
            {
                return false;
            }

            return true;
        }
    }
}
