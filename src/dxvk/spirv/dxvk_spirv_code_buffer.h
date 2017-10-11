#pragma once

#include <spirv/spirv.hpp>

#include <iostream>
#include <vector>

#include "../dxvk_include.h"

namespace dxvk {
  
  /**
   * \brief SPIR-V code buffer
   * 
   * Helper class for generating SPIR-V shaders.
   * Stores arbitrary SPIR-V instructions in a
   * format that can be read by Vulkan drivers.
   */
  class SpirvCodeBuffer {
    
  public:
    
    SpirvCodeBuffer();
    SpirvCodeBuffer(
      std::basic_istream<uint32_t>& stream);
    ~SpirvCodeBuffer();
    
    /**
     * \brief Code
     * \returns Code
     */
    const uint32_t* code() const {
      return m_code.data();
    }
    
    /**
     * \brief Code size, in bytes
     * \returns Code size, in bytes
     */
    size_t size() const {
      return m_code.size();
    }
    
    /**
     * \brief Merges two code buffers
     * 
     * This is useful to generate declarations or
     * the SPIR-V header at the same time as the
     * code when doing so in advance is impossible.
     * \param [in] other Code buffer to append
     */
    void append(const SpirvCodeBuffer& other);
    
    /**
     * \brief Appends an 32-bit word to the buffer
     * \param [in] word The word to append
     */
    void putWord(uint32_t word);
    
    /**
     * \brief Appends an instruction word to the buffer
     * 
     * Adds a single word containing both the word count
     * and the op code number for a single instruction.
     * \param [in] opCode Operand code
     * \param [in] wordCount Number of words
     */
    void putIns(spv::Op opCode, uint16_t wordCount);
    
    /**
     * \brief Appends a 32-bit integer to the buffer
     * \param [in] value The number to add
     */
    void putInt32(uint32_t word);
    
    /**
     * \brief Appends a 64-bit integer to the buffer
     * 
     * A 64-bit integer will take up two 32-bit words.
     * \param [in] value 64-bit value to add
     */
    void putInt64(uint64_t value);
    
    /**
     * \brief Appends a 32-bit float to the buffer
     * \param [in] value The number to add
     */
    void putFloat32(float value);
    
    /**
     * \brief Appends a 64-bit float to the buffer
     * \param [in] value The number to add
     */
    void putFloat64(double value);
    
    /**
     * \brief Appends a literal string to the buffer
     * \param [in] str String to append to the buffer
     */
    void putStr(const char* str);
    
    /**
     * \brief Adds the header to the buffer
     * \param [in] boundIds Number of bound IDs
     */
    void putHeader(uint32_t boundIds);
    
    /**
     * \brief Computes length of a literal string
     * 
     * \param [in] str The string to check
     * \returns Number of words consumed by a string
     */
    uint32_t strLen(const char* str);
    
    /**
     * \brief Stores the SPIR-V module to a stream
     * 
     * The ability to save modules to a file
     * exists mostly for debugging purposes.
     * \param [in] stream Output stream
     */
    void store(std::basic_ostream<uint32_t>& stream) const;
    
  private:
    
    std::vector<uint32_t> m_code;
    
  };
  
}