
/*

  KLayout Layout Viewer
  Copyright (C) 2006-2018 Matthias Koefferlein

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

*/

/**
*  @file gsiDeclQXmlSchema.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include <QXmlSchema>
#include <QAbstractMessageHandler>
#include <QAbstractUriResolver>
#include <QIODevice>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QXmlNamePool>
#include "gsiQt.h"
#include "gsiQtXmlPatternsCommon.h"
#include "gsiDeclQtXmlPatternsTypeTraits.h"
#include <memory>

// -----------------------------------------------------------------------
// class QXmlSchema

//  Constructor QXmlSchema::QXmlSchema()


static void _init_ctor_QXmlSchema_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return_new<QXmlSchema> ();
}

static void _call_ctor_QXmlSchema_0 (const qt_gsi::GenericStaticMethod * /*decl*/, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<QXmlSchema *> (new QXmlSchema ());
}


//  Constructor QXmlSchema::QXmlSchema(const QXmlSchema &other)


static void _init_ctor_QXmlSchema_2292 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QXmlSchema & > (argspec_0);
  decl->set_return_new<QXmlSchema> ();
}

static void _call_ctor_QXmlSchema_2292 (const qt_gsi::GenericStaticMethod * /*decl*/, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const QXmlSchema &arg1 = args.read<const QXmlSchema & > (heap);
  ret.write<QXmlSchema *> (new QXmlSchema (arg1));
}


// QUrl QXmlSchema::documentUri()


static void _init_f_documentUri_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QUrl > ();
}

static void _call_f_documentUri_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<QUrl > ((QUrl)((QXmlSchema *)cls)->documentUri ());
}


// bool QXmlSchema::isValid()


static void _init_f_isValid_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<bool > ();
}

static void _call_f_isValid_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<bool > ((bool)((QXmlSchema *)cls)->isValid ());
}


// bool QXmlSchema::load(const QUrl &source)


static void _init_f_load_1701 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("source");
  decl->add_arg<const QUrl & > (argspec_0);
  decl->set_return<bool > ();
}

static void _call_f_load_1701 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const QUrl &arg1 = args.read<const QUrl & > (heap);
  ret.write<bool > ((bool)((QXmlSchema *)cls)->load (arg1));
}


// bool QXmlSchema::load(QIODevice *source, const QUrl &documentUri)


static void _init_f_load_3040 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("source");
  decl->add_arg<QIODevice * > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("documentUri", true, "QUrl()");
  decl->add_arg<const QUrl & > (argspec_1);
  decl->set_return<bool > ();
}

static void _call_f_load_3040 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  QIODevice *arg1 = args.read<QIODevice * > (heap);
  const QUrl &arg2 = args ? args.read<const QUrl & > (heap) : (const QUrl &)(QUrl());
  ret.write<bool > ((bool)((QXmlSchema *)cls)->load (arg1, arg2));
}


// bool QXmlSchema::load(const QByteArray &data, const QUrl &documentUri)


static void _init_f_load_3902 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("data");
  decl->add_arg<const QByteArray & > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("documentUri", true, "QUrl()");
  decl->add_arg<const QUrl & > (argspec_1);
  decl->set_return<bool > ();
}

static void _call_f_load_3902 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const QByteArray &arg1 = args.read<const QByteArray & > (heap);
  const QUrl &arg2 = args ? args.read<const QUrl & > (heap) : (const QUrl &)(QUrl());
  ret.write<bool > ((bool)((QXmlSchema *)cls)->load (arg1, arg2));
}


// QAbstractMessageHandler *QXmlSchema::messageHandler()


static void _init_f_messageHandler_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QAbstractMessageHandler * > ();
}

static void _call_f_messageHandler_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<QAbstractMessageHandler * > ((QAbstractMessageHandler *)((QXmlSchema *)cls)->messageHandler ());
}


// QXmlNamePool QXmlSchema::namePool()


static void _init_f_namePool_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QXmlNamePool > ();
}

static void _call_f_namePool_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<QXmlNamePool > ((QXmlNamePool)((QXmlSchema *)cls)->namePool ());
}


// QNetworkAccessManager *QXmlSchema::networkAccessManager()


static void _init_f_networkAccessManager_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QNetworkAccessManager * > ();
}

static void _call_f_networkAccessManager_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<QNetworkAccessManager * > ((QNetworkAccessManager *)((QXmlSchema *)cls)->networkAccessManager ());
}


// QXmlSchema &QXmlSchema::operator=(const QXmlSchema &other)


static void _init_f_operator_eq__2292 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QXmlSchema & > (argspec_0);
  decl->set_return<QXmlSchema & > ();
}

static void _call_f_operator_eq__2292 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const QXmlSchema &arg1 = args.read<const QXmlSchema & > (heap);
  ret.write<QXmlSchema & > ((QXmlSchema &)((QXmlSchema *)cls)->operator= (arg1));
}


// void QXmlSchema::setMessageHandler(QAbstractMessageHandler *handler)


static void _init_f_setMessageHandler_2934 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("handler");
  decl->add_arg<QAbstractMessageHandler * > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setMessageHandler_2934 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  QAbstractMessageHandler *arg1 = args.read<QAbstractMessageHandler * > (heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QXmlSchema *)cls)->setMessageHandler (arg1);
}


// void QXmlSchema::setNetworkAccessManager(QNetworkAccessManager *networkmanager)


static void _init_f_setNetworkAccessManager_2742 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("networkmanager");
  decl->add_arg<QNetworkAccessManager * > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setNetworkAccessManager_2742 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  QNetworkAccessManager *arg1 = args.read<QNetworkAccessManager * > (heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QXmlSchema *)cls)->setNetworkAccessManager (arg1);
}


// void QXmlSchema::setUriResolver(const QAbstractUriResolver *resolver)


static void _init_f_setUriResolver_3372 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("resolver");
  decl->add_arg<const QAbstractUriResolver * > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setUriResolver_3372 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  tl::Heap heap;
  const QAbstractUriResolver *arg1 = args.read<const QAbstractUriResolver * > (heap);
  __SUPPRESS_UNUSED_WARNING(ret);
  ((QXmlSchema *)cls)->setUriResolver (arg1);
}


// const QAbstractUriResolver *QXmlSchema::uriResolver()


static void _init_f_uriResolver_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<const QAbstractUriResolver * > ();
}

static void _call_f_uriResolver_c0 (const qt_gsi::GenericMethod * /*decl*/, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  __SUPPRESS_UNUSED_WARNING(args);
  ret.write<const QAbstractUriResolver * > ((const QAbstractUriResolver *)((QXmlSchema *)cls)->uriResolver ());
}



namespace gsi
{

static gsi::Methods methods_QXmlSchema () {
  gsi::Methods methods;
  methods += new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QXmlSchema::QXmlSchema()\nThis method creates an object of class QXmlSchema.", &_init_ctor_QXmlSchema_0, &_call_ctor_QXmlSchema_0);
  methods += new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QXmlSchema::QXmlSchema(const QXmlSchema &other)\nThis method creates an object of class QXmlSchema.", &_init_ctor_QXmlSchema_2292, &_call_ctor_QXmlSchema_2292);
  methods += new qt_gsi::GenericMethod ("documentUri", "@brief Method QUrl QXmlSchema::documentUri()\n", true, &_init_f_documentUri_c0, &_call_f_documentUri_c0);
  methods += new qt_gsi::GenericMethod ("isValid?", "@brief Method bool QXmlSchema::isValid()\n", true, &_init_f_isValid_c0, &_call_f_isValid_c0);
  methods += new qt_gsi::GenericMethod ("load", "@brief Method bool QXmlSchema::load(const QUrl &source)\n", false, &_init_f_load_1701, &_call_f_load_1701);
  methods += new qt_gsi::GenericMethod ("load", "@brief Method bool QXmlSchema::load(QIODevice *source, const QUrl &documentUri)\n", false, &_init_f_load_3040, &_call_f_load_3040);
  methods += new qt_gsi::GenericMethod ("load", "@brief Method bool QXmlSchema::load(const QByteArray &data, const QUrl &documentUri)\n", false, &_init_f_load_3902, &_call_f_load_3902);
  methods += new qt_gsi::GenericMethod (":messageHandler", "@brief Method QAbstractMessageHandler *QXmlSchema::messageHandler()\n", true, &_init_f_messageHandler_c0, &_call_f_messageHandler_c0);
  methods += new qt_gsi::GenericMethod ("namePool", "@brief Method QXmlNamePool QXmlSchema::namePool()\n", true, &_init_f_namePool_c0, &_call_f_namePool_c0);
  methods += new qt_gsi::GenericMethod (":networkAccessManager", "@brief Method QNetworkAccessManager *QXmlSchema::networkAccessManager()\n", true, &_init_f_networkAccessManager_c0, &_call_f_networkAccessManager_c0);
  methods += new qt_gsi::GenericMethod ("assign", "@brief Method QXmlSchema &QXmlSchema::operator=(const QXmlSchema &other)\n", false, &_init_f_operator_eq__2292, &_call_f_operator_eq__2292);
  methods += new qt_gsi::GenericMethod ("setMessageHandler|messageHandler=", "@brief Method void QXmlSchema::setMessageHandler(QAbstractMessageHandler *handler)\n", false, &_init_f_setMessageHandler_2934, &_call_f_setMessageHandler_2934);
  methods += new qt_gsi::GenericMethod ("setNetworkAccessManager|networkAccessManager=", "@brief Method void QXmlSchema::setNetworkAccessManager(QNetworkAccessManager *networkmanager)\n", false, &_init_f_setNetworkAccessManager_2742, &_call_f_setNetworkAccessManager_2742);
  methods += new qt_gsi::GenericMethod ("setUriResolver|uriResolver=", "@brief Method void QXmlSchema::setUriResolver(const QAbstractUriResolver *resolver)\n", false, &_init_f_setUriResolver_3372, &_call_f_setUriResolver_3372);
  methods += new qt_gsi::GenericMethod (":uriResolver", "@brief Method const QAbstractUriResolver *QXmlSchema::uriResolver()\n", true, &_init_f_uriResolver_c0, &_call_f_uriResolver_c0);
  return methods;
}

gsi::Class<QXmlSchema> decl_QXmlSchema ("QtXmlPatterns", "QXmlSchema",
  methods_QXmlSchema (),
  "@qt\n@brief Binding of QXmlSchema");


GSI_QTXMLPATTERNS_PUBLIC gsi::Class<QXmlSchema> &qtdecl_QXmlSchema () { return decl_QXmlSchema; }

}
