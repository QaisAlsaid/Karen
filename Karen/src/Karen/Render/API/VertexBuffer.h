#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <cstdint>
#include "Karen/Core/Core.h"
#include "Karen/Render/API/BufferLayout.h"

namespace Karen
{
  class KAREN_API VertexBuffer
  {
  public:
    virtual ~VertexBuffer();

    virtual void bind()   const = 0;
    virtual void unbind() const = 0;
    virtual void setData(uint32_t size, const void* data = nullptr) = 0;
    virtual void setLayout(const BufferLayout& layout) = 0;
    virtual const BufferLayout& getLayout() const = 0;
    
    static ARef<VertexBuffer> create(uint32_t size, const float* data = nullptr);
  };
}

#endif //VERTEX_BUFFER_H
