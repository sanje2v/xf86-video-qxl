#include <string.h>
#include "qxl.h"

struct ring
{
    struct qxl_ring_header	header;
    uint8_t			elements[0];
};

struct qxl_ring
{
    struct ring *	ring;
    int			element_size;
    int			n_elements;
    int			prod_notify;
};

struct qxl_ring *
qxl_ring_create (struct qxl_ring_header *header,
		 int                     element_size,
		 int                     n_elements,
		 int			 prod_notify)
{
    struct qxl_ring *ring;

    ring = malloc (sizeof *ring);
    if (!ring)
	return NULL;

    ring->ring = (struct ring *)header;
    ring->element_size = element_size;
    ring->n_elements = n_elements;
    ring->prod_notify = prod_notify;
    
    return ring;
}

void
qxl_ring_push (struct qxl_ring *ring,
	       const void      *new_elt)
{
    struct qxl_ring_header *header = &(ring->ring->header);
    uint8_t *elt;
    int idx;

    while (header->prod - header->cons == header->num_items)
    {
	header->notify_on_cons = header->cons + 1;

	mem_barrier();
    }

    idx = header->prod & (ring->n_elements - 1);
    elt = ring->ring->elements + idx * ring->element_size;

    memcpy (elt, new_elt, ring->element_size);

    header->prod++;

    mem_barrier();

    if (header->prod == header->notify_on_prod)
	outb (ring->prod_notify, 0);
}

void
qxl_ring_pop (struct qxl_ring *ring,
	      void            *element)
{
#if 0
    struct qxl_ring_header *header = &(ring->ring->header);
    uint8_t *elt;
    int idx;
#endif

    /* FIXME */
}
