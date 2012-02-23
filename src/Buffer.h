#ifndef Magnum_Buffer_h
#define Magnum_Buffer_h
/*
    Copyright © 2010, 2011, 2012 Vladimír Vondruš <mosra@centrum.cz>

    This file is part of Magnum.

    Magnum is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License version 3
    only, as published by the Free Software Foundation.

    Magnum is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU Lesser General Public License version 3 for more details.
*/

/** @file
 * @brief Class Magnum::Buffer
 */

#include "Magnum.h"

namespace Magnum {

/**
 * @brief Class for managing buffers
 */
class Buffer {
    Buffer(const Buffer& other) = delete;
    Buffer(Buffer&& other) = delete;
    Buffer& operator=(const Buffer& other) = delete;
    Buffer& operator=(Buffer&& other) = delete;

    public:
        /** @brief %Buffer target */
        enum class Target: GLenum {
            /** Used for storing vertex attributes. */
            Array = GL_ARRAY_BUFFER,

            /** Source for copies. */
            CopyRead = GL_COPY_READ_BUFFER,

            /** Target for copies. */
            CopyWrite = GL_COPY_WRITE_BUFFER,

            /** Used for storing vertex indices. */
            ElementArray = GL_ELEMENT_ARRAY_BUFFER,

            /** Source for texture update operations. */
            PixelUnpack = GL_PIXEL_UNPACK_BUFFER,

            /** Target for pixel pack operations. */
            PixelPack = GL_PIXEL_PACK_BUFFER,

            /** Source for texel fetches. */
            Texture = GL_TEXTURE_BUFFER,

            /** Target for transform feedback. */
            TransformFeedback = GL_TRANSFORM_FEEDBACK_BUFFER,

            /** Used for storing uniforms. */
            Uniform = GL_UNIFORM_BUFFER
        };

        /** @brief Buffer usage */
        enum class Usage: GLenum {
            /**
             * Set once by the application and used infrequently for drawing.
             */
            StreamDraw = GL_STREAM_DRAW,

            /**
             * Set once as output from an OpenGL command and used infequently
             * for drawing.
             */
            StreamRead = GL_STREAM_READ,

            /**
             * Set once as output from an OpenGL command and used infrequently
             * for drawing or copying to other buffers.
             */
            StreamCopy = GL_STREAM_COPY,

            /**
             * Set once by the application and used frequently for drawing.
             */
            StaticDraw = GL_STATIC_DRAW,

            /**
             * Set once as output from an OpenGL command and queried many
             * times by the application.
             */
            StaticRead = GL_STATIC_READ,

            /**
             * Set once as output from an OpenGL command and used frequently
             * for drawing or copying to other buffers.
             */
            StaticCopy = GL_STATIC_COPY,

            /**
             * Updated frequently by the application and used frequently
             * for drawing or copying to other images.
             */
            DynamicDraw = GL_DYNAMIC_DRAW,

            /**
             * Updated frequently as output from OpenGL command and queried
             * many times from the application.
             */
            DynamicRead = GL_DYNAMIC_READ,

            /**
             * Updated frequently as output from OpenGL command and used
             * frequently for drawing or copying to other images.
             */
            DynamicCopy = GL_DYNAMIC_COPY
        };

        /**
         * @brief Unbind any buffer from given target
         * @param target     %Target
         */
        inline static void unbind(Target target) {
            glBindBuffer(static_cast<GLenum>(target), 0);
        }

        /**
         * @brief Constructor
         * @param defaultTarget Default target (used when calling bind()
         *      without parameter)
         *
         * Generates new OpenGL buffer.
         */
        inline Buffer(Target defaultTarget): _defaultTarget(defaultTarget) {
            glGenBuffers(1, &buffer);
        }

        /**
         * @brief Destructor
         *
         * Deletes associated OpenGL buffer.
         */
        inline virtual ~Buffer() {
            glDeleteBuffers(1, &buffer);
        }

        /** @brief Default bind type */
        inline Target defaultTarget() const { return _defaultTarget; }

        /**
         * @brief Bind buffer
         *
         * Binds buffer with default target.
         */
        inline void bind() const { bind(_defaultTarget); }

        /**
         * @brief Bind buffer
         * @param target     %Target
         */
        inline void bind(Target target) const {
            glBindBuffer(static_cast<GLenum>(target), buffer);
        }

        /**
         * @brief Set buffer data
         * @param size      Data size
         * @param data      Pointer to data
         * @param usage     %Buffer usage
         *
         * Sets buffer data with default target.
         */
        inline void setData(GLsizeiptr size, const GLvoid* data, Usage usage) {
            setData(_defaultTarget, size, data, usage);
        }

        /**
         * @brief Set buffer data
         * @param target    %Target
         * @param size      Data size
         * @param data      Pointer to data
         * @param usage     %Buffer usage
         */
        inline void setData(Target target, GLsizeiptr size, const GLvoid* data, Usage usage) {
            bind(target);
            glBufferData(static_cast<GLenum>(target), size, data, static_cast<GLenum>(usage));
        }

    private:
        GLuint buffer;
        Target _defaultTarget;
};

}

#endif
