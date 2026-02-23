#include "fig.h"
#include <cmath>

Figures2D::Figures2D() {

}

Figures2D::~Figures2D() {

}

void Figures2D::createTriangle(size_t num) {
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
            m_vertices.append({x, y, m_minVal + (row+col) * val_step});
        }
    }
    for (size_t row = 0; row < rowNum; row++) {
        for (size_t col = 0; col < colNum-1; col++) {
            size_t currIndex = row * colNum + col;
            if (row % 2 == 0) {
                m_indices.append({currIndex, currIndex+1, currIndex+colNum});
            } else {
                m_indices.append({currIndex, currIndex+1, currIndex-colNum+1});
            }
        }
    }
}

void Figures2D::createSimpleCase()
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
            m_vertices.append({x, y, (row+col) * val_step});
        }
    }
    for (size_t row = 0; row < rowNum; row++) {
        for (size_t col = 0; col < colNum-1; col++) {
            size_t currIndex = row * colNum + col;
            if (row % 2 == 0) {
                m_indices.append({currIndex, currIndex+1, currIndex+colNum});
            } else {
                m_indices.append({currIndex, currIndex+1, currIndex-colNum+1});
            }
        }
    }
}


