#pragma once
#ifndef BLOCK_HPP
#define BLOCK_HPP

// positions           // tex cord    // type

float quadVerticesFront[] = {
     0.5f,  0.5f,  0.5f,    1.0f, 1.0f,    0.0f,
     0.5f, -0.5f,  0.5f,    1.0f, 0.0f,    0.0f,
    -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,    0.0f,
    -0.5f,  0.5f,  0.5f,    0.0f, 1.0f,    0.0f
};

float quadVerticesRight[] = {
    -0.5f,  0.5f,  0.5f,    1.0f, 1.0f,    0.0f,
    -0.5f, -0.5f,  0.5f,    1.0f, 0.0f,    0.0f,
    -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,    0.0f,
    -0.5f,  0.5f, -0.5f,    0.0f, 1.0f,    0.0f
};

float quadVerticesBack[] = {
    -0.5f,  0.5f,  -0.5f,   1.0f, 1.0f,    0.0f,
    -0.5f, -0.5f,  -0.5f,   1.0f, 0.0f,    0.0f,
     0.5f, -0.5f,  -0.5f,   0.0f, 0.0f,    0.0f,
     0.5f,  0.5f,  -0.5f,   0.0f, 1.0f,    0.0f
};

float quadVerticesLeft[] = {
     0.5f,  0.5f,  -0.5f,   1.0f, 1.0f,    0.0f,
     0.5f, -0.5f,  -0.5f,   1.0f, 0.0f,    0.0f,
     0.5f, -0.5f,   0.5f,   0.0f, 0.0f,    0.0f,
     0.5f,  0.5f,   0.5f,   0.0f, 1.0f,    0.0f
};

float quadVerticesTop[] = {
    -0.5f,  0.5f,  0.5f,    1.0f, 1.0f,    0.0f,
    -0.5f,  0.5f, -0.5f,    1.0f, 0.0f,    0.0f,
     0.5f,  0.5f, -0.5f,    0.0f, 0.0f,    0.0f,
     0.5f,  0.5f,  0.5f,    0.0f, 1.0f,    0.0f
};

float quadVerticesBottom[] = {
    -0.5f,  -0.5f,  0.5f,    1.0f, 1.0f,    0.0f,
    -0.5f,  -0.5f, -0.5f,    1.0f, 0.0f,    0.0f,
     0.5f,  -0.5f, -0.5f,    0.0f, 0.0f,    0.0f,
     0.5f,  -0.5f,  0.5f,    0.0f, 1.0f,    0.0f
};

unsigned int quadIndices[] = {
    0, 1, 3,
    1, 2, 3
};

#endif