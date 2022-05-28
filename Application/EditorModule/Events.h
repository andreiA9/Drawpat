#ifndef EVENTS_H
#define EVENTS_H


class Events
{
public:
    Events();

    /** \brief specifies if an image rotate event was sent
      * \param imageRotated - if the rotate event was triggered
      */
    void setImageRoted(bool rotated) { m_imageRotated = rotated; }

    bool getImageRotated() const { return m_imageRotated; }

private:
    bool m_imageRotated;
};

#endif // EVENTS_H
