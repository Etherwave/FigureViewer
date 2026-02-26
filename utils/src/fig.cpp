#include "fig.h"
#include <cmath>

FieldGeometry2D::FieldGeometry2D() {

}

FieldGeometry2D::~FieldGeometry2D() {

}

void FieldGeometry2D::createTriangle(size_t num) {
    m_minX = -1000;
    m_maxX = 1000;
    m_minY = -1000;
    m_maxY = 1000;
    // m_minX = -1.0;
    // m_maxX = 1.0;
    // m_minY = -1.0;
    // m_maxY = 1.0;
    m_minVal = -1000;
    m_maxVal = 1000;
    m_minColor = {0, 0, 1};
    m_maxColor = {1, 0, 0};
    size_t rowNum = num;
    size_t colNum = rowNum;
    float x_step = (m_maxX - m_minX) / colNum;
    float y_step = (m_maxY - m_minY) / rowNum;
    float val_step = (m_maxVal - m_minVal) / (rowNum + colNum);
    for (size_t row = 0; row < rowNum; row++) {
        for (size_t col = 0; col < colNum; col++) {
            float x = m_minX + x_step * (col + 0.5f);
            float y = m_minY + y_step * (row + 0.5f);
            // m_vertices.append({x, y, (row+col) * val_step});
            m_vertexData.append({x, y, m_minVal + (row+col) * val_step});
        }
    }
    for (size_t row = 0; row < rowNum; row++) {
        for (size_t col = 0; col < colNum-1; col++) {
            size_t currIndex = row * colNum + col;
            if (row % 2 == 0) {
                m_elementTri.append({currIndex, currIndex+1, currIndex+colNum});
            } else {
                m_elementTri.append({currIndex, currIndex+1, currIndex-colNum+1});
            }
        }
    }
}

void FieldGeometry2D::createSimpleCase()
{
    m_minX = -1.0;
    m_maxX = 1.0;
    m_minY = -1.0;
    m_maxY = 1.0;
    m_minVal = -1;
    m_maxVal = 1;
    m_minColor = {0, 0, 1};
    m_maxColor = {1, 0, 0};
    size_t rowNum = 2;
    size_t colNum = rowNum;
    float x_step = (m_maxX - m_minX) / colNum;
    float y_step = (m_maxY - m_minY) / rowNum;
    float val_step = (m_maxVal - m_minVal) / (rowNum + colNum);
    for (size_t row = 0; row < rowNum; row++) {
        for (size_t col = 0; col < colNum; col++) {
            float x = m_minX + x_step * (col + 0.5f);
            float y = m_minY + y_step * (row + 0.5f);
            m_vertexData.append({x, y, (row+col) * val_step});
        }
    }
    for (size_t row = 0; row < rowNum; row++) {
        for (size_t col = 0; col < colNum-1; col++) {
            size_t currIndex = row * colNum + col;
            if (row % 2 == 0) {
                m_elementTri.append({currIndex, currIndex+1, currIndex+colNum});
            } else {
                m_elementTri.append({currIndex, currIndex+1, currIndex-colNum+1});
            }
        }
    }
}

void FieldGeometry2D::createRectangle(size_t rowNum, size_t colNum) {
    m_minX = -1000;
    m_maxX = 1000;
    m_minY = -1000;
    m_maxY = 1000;
    m_minVal = -1000;
    m_maxVal = 1000;
    m_minColor = {0, 0, 1};
    m_maxColor = {1, 0, 0};
    float x_step = (m_maxX - m_minX) / colNum;
    float y_step = (m_maxY - m_minY) / rowNum;
    float val_step = (m_maxVal - m_minVal) / (rowNum + colNum);
    for (size_t row = 0; row < rowNum; row++) {
        for (size_t col = 0; col < colNum; col++) {
            float x = m_minX + x_step * (col + 0.5f);
            float y = m_minY + y_step * (row + 0.5f);
            // m_vertices.append({x, y, (row+col) * val_step});
            m_vertexData.append({x, y, m_minVal + (row+col) * val_step});
        }
    }
    for (size_t row = 0; row < rowNum-1; row++) {
        for (size_t col = 0; col < colNum-1; col++) {
            int currIndex = row * colNum + col;
            m_elementTri.append({currIndex, currIndex+1, currIndex+colNum});
            m_elementTri.append({currIndex+colNum, currIndex+1, currIndex+colNum+1});
            m_elementLine.append({
                currIndex, currIndex+1,
                currIndex+1, currIndex+colNum+1,
                currIndex+colNum+1, currIndex+colNum,
                currIndex+colNum, currIndex
            });
        }
    }
}


