#include "engine/utilities/rendering/Texture2D.h"

namespace EisEngine {
    Texture2D::Texture2D() :
    Width(0), Height(0), internalFormat(GL_RGB), imageFormat(GL_RGB), wrapS(GL_CLAMP_TO_EDGE), wrapT(GL_CLAMP_TO_EDGE),
    minFilterMode(GL_LINEAR), maxFilterMode(GL_LINEAR)
    { glGenTextures(1, &textureID);}

    void Texture2D::Generate(unsigned int width, unsigned int height, unsigned char *data) {
        Width = width;
        Height = height;
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, (GLint) internalFormat, (GLint) width,
                     (GLint) height,0,imageFormat,GL_UNSIGNED_BYTE,data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint) wrapS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint) wrapT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint) minFilterMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint) maxFilterMode);

        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture2D::Bind() const { glBindTexture(GL_TEXTURE_2D, textureID);}
}