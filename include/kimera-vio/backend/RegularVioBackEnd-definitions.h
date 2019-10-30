/* ----------------------------------------------------------------------------
 * Copyright 2017, Massachusetts Institute of Technology,
 * Cambridge, MA 02139
 * All Rights Reserved
 * Authors: Luca Carlone, et al. (see THANKS for the full author list)
 * See LICENSE for the license information
 * -------------------------------------------------------------------------- */

/**
 * @file   VioBackEnd-definitions.h
 * @brief  Definitions for VioBackEnd.
 * @author Antoni Rosinol
 */

#pragma once

#include <vector>

#include <boost/optional.hpp>

#include <glog/logging.h>

#include <gtsam/geometry/Cal3_S2.h>
#include <gtsam/geometry/StereoPoint2.h>
#include <gtsam_unstable/nonlinear/IncrementalFixedLagSmoother.h>
#include <gtsam_unstable/slam/SmartStereoProjectionPoseFactor.h>

#include "kimera-vio/common/vio_types.h"
#include "kimera-vio/frontend/StereoVisionFrontEnd-definitions.h"
#include "kimera-vio/frontend/Tracker-definitions.h"
#include "kimera-vio/imu-frontend/ImuFrontEnd-definitions.h"
#include "kimera-vio/imu-frontend/ImuFrontEnd.h"
#include "kimera-vio/utils/Macros.h"
#include "kimera-vio/utils/UtilsOpenCV.h"

namespace VIO {

enum class RegularBackendModality {
  STRUCTURELESS = 0,  //! Only use structureless factors, equiv to normal Vio.
  PROJECTION = 1,  //! Converts all structureless factors to projection factors.
  STRUCTURELESS_AND_PROJECTION =
      2,                          //! Projection factors used for regularities.
  PROJECTION_AND_REGULARITY = 3,  //! Projection Vio + regularity factors.
  STRUCTURELESS_PROJECTION_AND_REGULARITY = 4  //! All types of factors used.
};

}  // namespace VIO
