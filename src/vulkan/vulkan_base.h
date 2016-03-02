//---- src/vulkan/vulkan_base.h - Provides minimal vulkan functionality -----//
//
//                        Vulkan Examples/Tutorials
//                          
//                        Copyright (c) 2016 Rob Clucas        
//                      Distributed under the MIT License
//                (See accompanying file LICENSE or copy at
//                    https://opensource.org/licenses/MIT)
//
// ========================================================================= //
//
// \file   vulkan_base.h
// \brief  Defines a class with minimal basic functionality -- this is designed
// as a base class which should be used by derived class wanting more specific
// functionality.
//---------------------------------------------------------------------------//

#ifndef VULKAN_VULKAN_VULKAN_BASE_H
#define VULKAN_VULKAN_VULKAN_BASE_H

#include "vulkan_wrapper.h"

// Class which has a vulkan instance and a all the physical devices supported.
// It can be used by other classes to extended the vulkan functionality more
// specifically.
class VulkanBase {
 public:
   // Constructor which:
   //   - Creates a Vulkan Instance
   //   - Enumerates Physical Devices
   //
   // \param appName The name of the vulkan application for this instance.
   // \param engineName The name of the engine for this application.
   // \param extensions The vulkan extensions to use.
   VulkanBase(const char* appName = "", const char* engineName = "",
     const std::vector<const char*>&extensions = std::vector<const char*>{});

  // Finds a queue for a specific physical device. If the queue is found, then
  // the function returns truw, otherwise it returns false.
  //
  // \note This function only sets the value of queueIdx if all of the flags
  // which are set are found.
  //
  // \param deviceIdx The index of the device to find the queue for.
  // \param queueFlags The queue to search for.
  // \param queueIdx The index of the queue
  bool findQueue(uint32_t deviceIdx, VkQueueFlagBits queueFlags, 
    uint32_t* queueIdx);
  
  // Gets a physical device from the available physical devices.
  //
  // \param deviceIdx The index of the device to set.
  VkPhysicalDevice getVkPhysicalDevice(size_t deviceIdx) const {
    return PhysicalDevices[deviceIdx];
  }

  // Gets the memory properties of a physical device.
  //
  // \param deviceIdx The index of the phsical device to get the memory
  // properties of.
  VkPhysicalDeviceMemoryProperties getVkPhysicalDeviceMemoryProperties(
      size_t deviceIdx) const {
    return PhysicalDevicesMemProps[deviceIdx];
  }

  // Gets a wrapper around a physical device and its memory properties for when
  // both are required.
  //
  // \param deviceIdx The index of the physical device and its memory to get.
  VwPhysicalDevice getVwPhysicalDevice(size_t deviceIdx) const {
    return VwPhysicalDevice(PhysicalDevices[deviceIdx], 
             PhysicalDevicesMemProps[deviceIdx]);
  }

  protected:
   VkInstance         Instance;                 // Store per-application state.
   VwPhysDeviceVec    PhysicalDevices;          // CPUs | GPUs for vulkan.
   VwPhysDeviceMemVec PhysicalDevicesMemProps;  // Devices memory properties.

  private:
   // Creates the vulkan instance.
   //
   // \param appName The name of the vulkan application.
   // \param engineName The name of the engine application.
   // \param extensions The extensions to enable for the instance.
   VkResult createInstance(const char* appName, const char* engineName,
     const std::vector<const char*>& extensions);

  // Gets all the physical devices which are available.
  void getPhysicalDevices();

  // Gets the memory properties of each of the physical devices.
  void getPhysicalDevicesMemoryProperties();
};

#endif  // VULKAN_VULKAN_VULKAN_BASE_H