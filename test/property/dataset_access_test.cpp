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

#include <gtest/gtest.h>
#include <h5cpp/property/dataset_access.hpp>
#include <h5cpp/property/property_class.hpp>
#include <h5cpp/hdf5.hpp>

namespace pl = hdf5::property;

TEST(DatasetAccessList, test_default_construction) {
  pl::DatasetAccessList dapl;
  EXPECT_TRUE(dapl.get_class() == pl::kDatasetAccess);

  auto cl = pl::kDatasetAccess;
  EXPECT_NO_THROW((pl::DatasetAccessList(hdf5::ObjectHandle(H5Pcreate(static_cast<hid_t>(cl))))));

  cl = pl::kGroupAccess;
  EXPECT_THROW((pl::DatasetAccessList(hdf5::ObjectHandle(H5Pcreate(static_cast<hid_t>(cl))))),
               std::runtime_error);

  cl = pl::kDatatypeCreate;
  EXPECT_THROW((pl::DatasetAccessList(hdf5::ObjectHandle(H5Pcreate(static_cast<hid_t>(cl))))),
               std::runtime_error);
}

#if H5_VERSION_GE(1, 10, 0)
TEST(DatasetAccessList, VirtualDataView) {
  std::stringstream stream;

  stream.str(std::string());
  stream << pl::VirtualDataView::FIRST_MISSING;
  EXPECT_EQ(stream.str(), "FIRST_MISSING");

  stream.str(std::string());
  stream << pl::VirtualDataView::LAST_AVAILABLE;
  EXPECT_EQ(stream.str(), "LAST_AVAILABLE");
}
#endif

TEST(DatasetAccessList, test_chunk_cache_parameters) {
  pl::ChunkCacheParameters def;
  pl::DatasetAccessList dapl;
  pl::ChunkCacheParameters params(200, 300 * 1024 * 1024, 0.5);
  EXPECT_NO_THROW(dapl.chunk_cache_parameters(params));
  pl::ChunkCacheParameters p2 = dapl.chunk_cache_parameters();

  EXPECT_EQ(def.chunk_slots(), 0ul);
  EXPECT_EQ(p2.chunk_slots(), 200ul);
  EXPECT_NO_THROW(p2.chunk_slots(400ul));
  EXPECT_EQ(p2.chunk_slots(), 400ul);

  EXPECT_EQ(def.chunk_cache_size(), 0ul);
  EXPECT_EQ(p2.chunk_cache_size(), 300ul * 1024ul * 1024ul);
  EXPECT_NO_THROW(p2.chunk_cache_size(30ul));
  EXPECT_EQ(p2.chunk_cache_size(), 30ul);

  EXPECT_NEAR(def.preemption_policy(), 0, 0.0001);
  EXPECT_NEAR(p2.preemption_policy(), 0.5, 0.0001);
  EXPECT_NO_THROW(p2.preemption_policy(0.4));
  EXPECT_NEAR(p2.preemption_policy(), 0.4, 0.0001);

  hdf5::ObjectHandle(static_cast<hid_t>(dapl)).close();
  EXPECT_THROW(dapl.chunk_cache_parameters(params), std::runtime_error);
  EXPECT_THROW(dapl.chunk_cache_parameters(), std::runtime_error);
}

#if H5_VERSION_GE(1, 10, 0)
TEST(DatasetAccessList, test_virtual_data_view) {
  pl::DatasetAccessList dapl;
  dapl.virtual_view(pl::VirtualDataView::FIRST_MISSING);
  EXPECT_EQ(dapl.virtual_view(), pl::VirtualDataView::FIRST_MISSING);

  dapl.virtual_view(pl::VirtualDataView::LAST_AVAILABLE);
  EXPECT_EQ(dapl.virtual_view(), pl::VirtualDataView::LAST_AVAILABLE);

  hdf5::ObjectHandle(static_cast<hid_t>(dapl)).close();
  EXPECT_THROW(dapl.virtual_view(), std::runtime_error);
  EXPECT_THROW(dapl.virtual_view(pl::VirtualDataView::FIRST_MISSING), std::runtime_error);
}

#endif


