#ifndef __DUI_REFERENCCOUNTEDOBJECT_H__
#define __UIEDIT_H__

#pragma once

class UILIB_API DuiRefCounter
{
public:
    //==============================================================================
    /** Increments the object's reference count.

        This is done automatically by the smart pointer, but is public just
        in case it's needed for nefarious purposes.
    */
    void incReferenceCount() noexcept
    {
        ++refCount;
    }

    /** Decreases the object's reference count.
        If the count gets to zero, the object will be deleted.
    */
    void decReferenceCount() noexcept
    {
        assert (getReferenceCount() > 0);

        if (--refCount == 0)
            delete this;
    }

    /** Decreases the object's reference count.
        If the count gets to zero, the object will not be deleted, but this method
        will return true, allowing the caller to take care of deletion.
    */
    bool decReferenceCountWithoutDeleting() noexcept
    {
        assert (getReferenceCount() > 0);
        return --refCount == 0;
    }

    /** Returns the object's current reference count. */
    int getReferenceCount() const noexcept       { return refCount.get(); }


protected:
    //==============================================================================
    /** Creates the reference-counted object (with an initial ref count of zero). */
    DuiRefCounter() {}

    /** Destructor. */
    virtual ~DuiRefCounter()
    {
        // it's dangerous to delete an object that's still referenced by something else!
        assert (getReferenceCount() == 0);
    }

    /** Resets the reference count to zero without deleting the object.
        You should probably never need to use this!
    */
    void resetReferenceCount() noexcept
    {
        refCount = 0;
    }

private:
    //==============================================================================
    std::atomic <int> refCount;

    DUI_DECLARE_NON_COPYABLE (DuiRefCounter)
};

#endif __DUI_REFERENCCOUNTEDOBJECT_H__