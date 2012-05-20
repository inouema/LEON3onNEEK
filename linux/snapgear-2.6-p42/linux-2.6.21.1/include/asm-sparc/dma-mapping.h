#ifndef _ASM_SPARC_DMA_MAPPING_H
#define _ASM_SPARC_DMA_MAPPING_H

#ifdef CONFIG_LEON
#include <asm/scatterlist.h>
/* 
 *  Function definitions in ioport.c
 */

extern int
dma_supported(struct device *dev, u64 mask);


extern int
dma_set_mask(struct device *dev, u64 dma_mask);

extern void *
dma_alloc_coherent(struct device *dev, size_t size, dma_addr_t *dma_handle,
		   gfp_t flag);

extern void
dma_free_coherent(struct device *dev, size_t size, void *cpu_addr,
		  dma_addr_t dma_handle);

extern dma_addr_t
dma_map_single(struct device *dev, void *cpu_addr, size_t size,
	       enum dma_data_direction direction);


extern void
dma_unmap_single(struct device *dev, dma_addr_t dma_addr, size_t size,
		 enum dma_data_direction direction);


extern dma_addr_t
dma_map_page(struct device *dev, struct page *page,
	     unsigned long offset, size_t size,
	     enum dma_data_direction direction);

extern void
dma_unmap_page(struct device *dev, dma_addr_t dma_address, size_t size,
	       enum dma_data_direction direction);


extern int
dma_map_sg(struct device *dev, struct scatterlist *sg, int nents,
	   enum dma_data_direction direction);

extern void
dma_unmap_sg(struct device *dev, struct scatterlist *sg, int nhwentries,
	     enum dma_data_direction direction);

extern void
dma_sync_single_for_cpu(struct device *dev, dma_addr_t dma_handle, size_t size,
			enum dma_data_direction direction);


extern void
dma_sync_single_for_device(struct device *dev, dma_addr_t dma_handle, size_t size,
			   enum dma_data_direction direction);

extern void
dma_sync_sg_for_cpu(struct device *dev, struct scatterlist *sg, int nelems,
		    enum dma_data_direction direction);


extern void
dma_sync_sg_for_device(struct device *dev, struct scatterlist *sg, int nelems,
		       enum dma_data_direction direction);


extern int
dma_mapping_error(dma_addr_t dma_addr);

#define dma_alloc_noncoherent(d, s, h, f) dma_alloc_coherent(d, s, h, f)
#define dma_free_noncoherent(d, s, v, h) dma_free_coherent(d, s, v, h)
#define dma_is_consistent(d, h)	(1)

#else
#ifdef CONFIG_PCI
#include <asm-generic/dma-mapping.h>
#else
#include <asm-generic/dma-mapping-broken.h>
#endif /* PCI */
#endif /* LEON */

#endif /* _ASM_SPARC_DMA_MAPPING_H */
