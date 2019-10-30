/* ----------------------------------------------------------------------------
 * Copyright 2017, Massachusetts Institute of Technology,
 * Cambridge, MA 02139
 * All Rights Reserved
 * Authors: Luca Carlone, et al. (see THANKS for the full author list)
 * See LICENSE for the license information
 * -------------------------------------------------------------------------- */

/**
 * @file   DataSource.h
 * @brief  Base implementation of a data provider for the VIO pipeline.
 * @author Antoni Rosinol
 */

#pragma once

#include <functional>
#include <string>

#include "kimera-vio/frontend/StereoImuSyncPacket.h"
#include "kimera-vio/pipeline/Pipeline-definitions.h"

namespace VIO {

class DataProviderInterface {
 public:
  typedef std::function<void(StereoImuSyncPacket::ConstUniquePtr)>
      VioInputCallback;

  /** Regular ctor.
   *   [in] initial_k: first frame id to be parsed.
   *   [in] final_k: last frame id to be parsed.
   *   [in] dataset_path: path to the Euroc dataset.
   **/
  DataProviderInterface(int initial_k,
                        int final_k,
                        const std::string& dataset_path);
  // Ctor from gflags. Calls regular ctor with gflags values.
  DataProviderInterface();
  virtual ~DataProviderInterface();

  // The derived classes need to implement this function!
  // Spin the dataset: processes the input data and constructs a Stereo Imu
  // Synchronized Packet which contains the minimum amount of information
  // for the VIO pipeline to do one processing iteration.
  // A Dummy example is provided as an implementation.
  virtual bool spin();

  // Init Vio parameters.
  PipelineParams pipeline_params_;

  // Register a callback function that will be called once a StereoImu Synchro-
  // nized packet is available for processing.
  void registerVioCallback(VioInputCallback callback);

 protected:
  // Vio callback. This function should be called once a StereoImuSyncPacket
  // is available for processing.
  VioInputCallback vio_callback_;

  FrameId initial_k_;  // start frame
  FrameId final_k_;    // end frame
  std::string dataset_path_;

protected:
 //! Helper functions to parse user-specified parameters.
 //! These are agnostic to dataset type.
 void parseBackendParams();
 void parseFrontendParams();
 void parseLCDParams();

 //! Functions to parse dataset dependent parameters.
 // Parse cam0, cam1 of a given dataset.
 virtual bool parseCameraParams(const std::string& input_dataset_path,
                                const std::string& left_cam_name,
                                const std::string& right_cam_name,
                                const bool parse_images,
                                MultiCameraParams* multi_cam_params) = 0;
 virtual bool parseImuParams(const std::string& input_dataset_path,
                             const std::string& imu_name) = 0;
};

}  // namespace VIO
