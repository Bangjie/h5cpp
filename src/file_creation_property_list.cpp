//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5pp.
//
// h5cpp is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// h5cpp is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  ee the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with h5cpp.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Aug 16, 2017
//

#include <stdexcept>
#include "property_list.hpp"

namespace hdf5 {
namespace property_list {

FileCreation::FileCreation():
    List(kFileCreate)
{
}

hsize_t FileCreation::userblock() const
{
  hsize_t buffer;
  if(H5Pget_userblock(static_cast<hid_t>(*this),&buffer)<0)
  {
    throw std::runtime_error("Cannot retrieve user block size from file creation property list!");
  }
  return buffer;
}

void FileCreation::userblock(hsize_t size) const
{
  if(H5Pset_userblock(static_cast<hid_t>(*this),size)<0)
  {
    throw std::runtime_error("Cannot set user block size for file creation property list!");
  }
}

void FileCreation::object_offset_size(size_t size) const
{
  if(H5Pset_sizes(static_cast<hid_t>(*this),size,object_length_size())<0)
  {
    throw std::runtime_error("Failure setting object offset size to file creation property list!");
  }
}

size_t FileCreation::object_offset_size() const
{
  size_t offset_size = 0,
         length_size = 0;

  if(H5Pget_sizes(static_cast<hid_t>(*this),&offset_size,&length_size)<0)
  {
    throw std::runtime_error("Failure retrieving object offset size from file creation property list!");
  }

  return offset_size;
}

void FileCreation::object_length_size(size_t size) const
{
  if(H5Pset_sizes(static_cast<hid_t>(*this),object_offset_size(),size)<0)
  {
    throw std::runtime_error("Failure setting object length size in file creation property list!");
  }
}

size_t FileCreation::object_length_size() const
{
  size_t offset_size = 0,
         length_size = 0;

  if(H5Pget_sizes(static_cast<hid_t>(*this),&offset_size,&length_size)<0)
  {
    throw std::runtime_error("Failure retrieving object length size from file creation property list!");
  }

  return length_size;
}

} // namespace property_list
} // namespace hdf5