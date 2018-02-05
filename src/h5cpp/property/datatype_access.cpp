//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5pp.
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.
//
// This library is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty ofMERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the
// Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor
// Boston, MA  02110-1301 USA
// ===========================================================================
//
// Authors:
//   Eugen Wintersberger <eugen.wintersberger@desy.de>
//   Martin Shetty <martin.shetty@esss.se>
// Created on: Aug 22, 2017
//

#include <h5cpp/property/datatype_access.hpp>
#include <h5cpp/property/property_class.hpp>
#include <sstream>

namespace hdf5 {
namespace property {

DatatypeAccessList::DatatypeAccessList():
    LinkAccessList(kDatatypeAccess)
{}

DatatypeAccessList::~DatatypeAccessList()
{}

DatatypeAccessList::DatatypeAccessList(ObjectHandle &&handle) :
    LinkAccessList(std::move(handle))
{
  if (get_class() != kDatatypeAccess) {
    std::stringstream ss;
    ss << "Cannot create property::DatatypeAccessList from " << get_class();
    throw std::runtime_error(ss.str());
  }
}


} // namespace property
} // namespace hdf5
