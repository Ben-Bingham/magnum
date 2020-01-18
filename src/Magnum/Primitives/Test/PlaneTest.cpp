/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019
              Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

#include <Corrade/TestSuite/Tester.h>

#include "Magnum/Mesh.h"
#include "Magnum/Math/Vector3.h"
#include "Magnum/Primitives/Plane.h"
#include "Magnum/Trade/MeshData.h"

namespace Magnum { namespace Primitives { namespace Test { namespace {

struct PlaneTest: TestSuite::Tester {
    explicit PlaneTest();

    void solid();
    void solidTextured();
    void wireframe();
};

PlaneTest::PlaneTest() {
    addTests({&PlaneTest::solid,
              &PlaneTest::solidTextured,
              &PlaneTest::wireframe});
}

void PlaneTest::solid() {
    Trade::MeshData plane = Primitives::planeSolid();

    CORRADE_COMPARE(plane.primitive(), MeshPrimitive::TriangleStrip);
    CORRADE_VERIFY(!plane.isIndexed());
    CORRADE_COMPARE(plane.vertexCount(), 4);
    CORRADE_COMPARE(plane.attributeCount(), 2);
    CORRADE_COMPARE(plane.attribute<Vector3>(Trade::MeshAttribute::Position)[3],
        (Vector3{-1.0f, 1.0f, 0.0f}));
    CORRADE_COMPARE(plane.attribute<Vector3>(Trade::MeshAttribute::Normal)[2],
        (Vector3{0.0f, 0.0f, 1.0f}));
}

void PlaneTest::solidTextured() {
    Trade::MeshData plane = Primitives::planeSolid(Primitives::PlaneTextureCoords::Generate);

    CORRADE_COMPARE(plane.primitive(), MeshPrimitive::TriangleStrip);
    CORRADE_VERIFY(!plane.isIndexed());
    CORRADE_COMPARE(plane.vertexCount(), 4);
    CORRADE_COMPARE(plane.attributeCount(), 3);
    CORRADE_COMPARE(plane.attribute<Vector3>(Trade::MeshAttribute::Position)[3],
        (Vector3{-1.0f, 1.0f, 0.0f}));
    CORRADE_COMPARE(plane.attribute<Vector3>(Trade::MeshAttribute::Normal)[2],
        (Vector3{0.0f, 0.0f, 1.0f}));
    CORRADE_COMPARE(plane.attribute<Vector2>(Trade::MeshAttribute::TextureCoordinates)[1],
        (Vector2{1.0f, 1.0f}));
}

void PlaneTest::wireframe() {
    Trade::MeshData plane = Primitives::planeWireframe();

    CORRADE_COMPARE(plane.primitive(), MeshPrimitive::LineLoop);
    CORRADE_VERIFY(!plane.isIndexed());
    CORRADE_COMPARE(plane.vertexCount(), 4);
    CORRADE_COMPARE(plane.attributeCount(), 1);
    CORRADE_COMPARE(plane.attribute<Vector3>(Trade::MeshAttribute::Position)[3],
        (Vector3{-1.0f, 1.0f, 0.0f}));
}

}}}}

CORRADE_TEST_MAIN(Magnum::Primitives::Test::PlaneTest)
