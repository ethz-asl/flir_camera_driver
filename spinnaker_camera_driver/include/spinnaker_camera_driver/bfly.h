#ifndef SPINNAKER_CAMERA_DRIVER_BFLY_H
#define SPINNAKER_CAMERA_DRIVER_BFLY_H
#include "spinnaker_camera_driver/camera.h"

namespace spinnaker_camera_driver {
class BFly : public Camera {
public:
  explicit BFly(Spinnaker::GenApi::INodeMap *node_map);
  ~BFly();
  void setFrameRate(const float frame_rate);
  void setNewConfiguration(const SpinnakerConfig& config,
                           const uint32_t& level);

private:
  void setImageControlFormats(
      const spinnaker_camera_driver::SpinnakerConfig &config);
};
} // namespace spinnaker_camera_driver
#endif // SPINNAKER_CAMERA_DRIVER_BFLY_H
