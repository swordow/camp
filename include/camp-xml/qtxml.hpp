/****************************************************************************
**
** Copyright (C) 2009-2014 TEGESO/TEGESOFT and/or its subsidiary(-ies) and mother company.
** Contact: Tegesoft Information (contact@tegesoft.com)
**
** This file is part of the CAMP library.
**
** The MIT License (MIT)
**
** Copyright (C) 2009-2014 TEGESO/TEGESOFT and/or its subsidiary(-ies) and mother company.
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** 
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Software.
** 
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
** THE SOFTWARE.
**
****************************************************************************/

#ifndef CAMP_XML_QTXML_HPP
#define CAMP_XML_QTXML_HPP

#include <camp-xml/common.hpp>
#include <QDomDocument>
#include <QDomElement>

namespace camp
{
namespace xml
{
namespace detail
{
/**
 * \brief Proxy that adapts the camp::xml functions to the QtXml library
 */
struct QtXml
{
    typedef QDomElement NodeType;

    static NodeType addChild(NodeType node, const std::string& name)
    {
        QDomElement child = node.ownerDocument().createElement(name.c_str());
        node.appendChild(child);
        return child;
    }

    static void setText(NodeType node, const std::string& text)
    {
        node.appendChild(node.ownerDocument().createTextNode(text.c_str()));
    }

    static NodeType findFirstChild(NodeType node, const std::string& name)
    {
        return node.firstChildElement(name.c_str());
    }

    static NodeType findNextSibling(NodeType node, const std::string& name)
    {
        return node.nextSiblingElement(name.c_str());
    }

    static std::string getText(NodeType node)
    {
        return node.text().toStdString();
    }

    static bool isValid(NodeType node)
    {
        return !node.isNull();
    }
};

} // namespace detail

/**
 * \brief Serialize a CAMP object into a QtXml QDomElement
 *
 * This function iterates over all the object's properties
 * and transforms them into valid XML nodes. Composed sub-objects
 * are serialized recursively.
 *
 * \a node is the parent node to which the generated child nodes
 * will be appended.
 *
 * You have the possibility to exclude some properties from the
 * generated output with the last (optional) parameter, \a exclude.
 * If it is defined, any property containing this value as a tag
 * will be excluded from the serialization process. It is empty
 * by default, which means that no property will be excluded.
 *
 * \param object Object to serialize
 * \param node Parent for the generated XML nodes
 * \param exclude Tag to exclude from the serialization process
 */
inline void serialize(const UserObject& object, QDomElement node, const Value& exclude = Value::nothing)
{
    detail::serialize<detail::QtXml>(object, node, exclude);
}

/**
 * \brief Deserialize a CAMP object from a QtXml QDomElement
 *
 * This function iterates over all the object's properties
 * and read their value from XML nodes. Composed sub-objects
 * are deserialized recursively.
 *
 * You have the possibility to exclude some properties from
 * being read with the last (optional) parameter, \a exclude.
 * If it is defined, any property containing this value as a tag
 * will be excluded from the deserialization process. It is empty
 * by default, which means that no property will be excluded.
 *
 * \param object Object to fill with deserialized information
 * \param node XML node to parse
 * \param exclude Tag to exclude from the deserialization process
 */
inline void deserialize(const UserObject& object, QDomElement node, const Value& exclude = Value::nothing)
{
    detail::deserialize<detail::QtXml>(object, node, exclude);
}

} // namespace xml

} // namespace camp

#endif // CAMP_XML_QTXML_HPP
