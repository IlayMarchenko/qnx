/*
 * Copyright (c) 2015-2016, NVIDIA CORPORATION. All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property
 * and proprietary rights in and to this software and related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA Corporation is strictly prohibited.
 */

#ifndef __NVDTCOMMON_H
#define __NVDTCOMMON_H

#include <errno.h>
#include <stdbool.h>
#include "nvdt_types.h"

/**
 * Get a pointer to the dtb blob in the syspage.
 *
 * @nvdt_ptr: Pointer to variable that will point to dtb blob.
             This variable will be updated by this function.
 * @nvdt_size: Pointer to interger variable to store nvdt size.
             If not NULL, this variable will be updated by this function.
 *
 * returns:
 *     NVDT_SUCCESS, if device tree blob is found in syspage.
 *     NVDT_NULL_PTR, if nvdt_ptr is NULL.
 *     NVDT_ERROR, otherwise.
 */
nvdt_error nvdt_get_fdt(void **nvdt_ptr, size_t *nvdt_size);

/**
 * Unmaps the dtb blob in syspage.
 *
 * @nvdt: Pointer to dtb blob.
 */
void nvdt_free_fdt(void *nvdt);

/**
 * Get the alias name from the aliases table in device tree.
 * This names should preferrably be used for devnode enumeration.
 *
 * @nvdt: Pointer to dtb blob.
 * @nvdt_node_offset: Offset of the device tree node.
 *
 * returns:
 *     pointer to the alias name if mapping for nvdt_node_offset is found.
 *     NULL, otherwise.
 */
const char *nvdt_get_alias_name(const void *nvdt, const int nvdt_node_name);

/**
 * Get (address, size) tupple from "reg" field in the given reg pointer.
 *
 * @reg: Pointer to the reg value.
 * @addr_cells: Number of address cells per tupple.
 * @size_cells: Number of size cells per tupple.
 * @tupple_num: The tupple number to read.
 * @addr: Pointer to store the address field. This field should be large enough
          to store the address value of size (address-cells * 4) bytes. This
          field can be NULL.
 * @size: Pointer to store the size field. This field should be large enough
          to store the size value of size (size-cells * 4) bytes. This field
          can be NULL.
 *
 * returns:
 *     NVDT_SUCCESS on success.
 *     NVDT_ERROR, otherwise.
 */
nvdt_error nvdt_get_reg_tupple(const uint32_t *reg, uint32_t addr_cells,
    uint32_t size_cells, int tupple_num, uint32_t *addr, uint32_t *size);

/**
 * Get (address, size) tupple from "reg" field in the node at the given offset.
 * NOTE: Avoid using this function in a loop to get all the tupples because the
 *       function tries to find the reg field everytime.
 *
 * @nvdt: Pointer to dtb blob.
 * @nvdt_node_offset: Offset of the device tree node.
 * @tupple_num: The tupple number to read.
 * @addr: Pointer to store the address field. This field should be large enough
          to store the address value of size (address-cells * 4) bytes.
 * @size: Pointer to store the size field. This field should be large enough
          to store the size value of size (size-cells * 4) bytes.
 *
 * returns:
 *     NVDT_SUCCESS on success.
 *     NVDT_ERROR, otherwise.
 */
nvdt_error nvdt_get_reg_tupple_by_offset(const void *nvdt, const int nvdt_node_offset,
    int tupple_num, uint32_t *addr, uint32_t *size);

/**
 * Checks if the device tree node is enabled.
 *
 * @nvdt: Pointer to the device tree blob.
 * @nvdt_node_offset: Offset of the device tree node.
 *
 * returns:
 *     1, if status is "okay" or status property is not present.
 *     0, otherwise.
 */
int nvdt_is_status_okay(const void *nvdt, const int nvdt_node_offset);

/**
 * nvdt_node_prop_count - caculate how many prop in a given node
 * @nvdt: pointer to the device tree blob
 * @node: offset of the node whose subnode to find
 *
 * nvdt_node_prop_count how many prop with a given node
 *
 * returns:
 *    count, caculate result for the given node
 */

uint32_t nvdt_node_prop_count(const void *nvdt, int node);

/**
 * nvdt_subnode_count - caculate how many subnode in a given node
 * @nvdt: pointer to the device tree blob
 * @node: offset of the node whose subnode to find
 * @depth: which depth to count for the given node
 *
 * nvdt_subnode_count how many subnode with a given node and depth
 * example:
 * root-node {
 *     node1{
 *        ....
 *        child-node1 {
 *            ....
 *        }
 *        child-node2 {
 *        }
 *    }
 *    node2{
 *        child-node3 {
 *        }
 *    }
 *    node3{
 *        child-node4 {
 *        }
 *    }
 *}
 * nvdt_subnode_count(root-node, 1), count result is 3 (node1 + node2 + node3).
 * nvdt_subnode_count(root-node, 2), count result is 4 (child-node1 + child-node2
 *   child-node3 + child-node4).
 *
 * returns:
 *    count, caculate result for the given node and depth
 */
uint32_t nvdt_subnode_count(const void *nvdt, int node, uint32_t depth);

/**
 * nvdt_get_addr_size - Find the applicable #address-cell & #size-cell for this node.
 * Please note that lookup starts from this node.
 * and continues it's parent till the / node is reached
 *
 * if current node has #address-cell and #size-cell then use them.
 * if it doesn't have them, then lookup them in its parent.
 *
 * returns: NO_ERROR
 */
int  nvdt_get_addr_size(const void *nvdt, int node, int *addr_cells,
        int *size_cells);

/**
 * nvdt_read_array_by_index - get the array value of a give prop name and index in a node.
 * @nvdt: pointer to the device tree blob
 * @nodeoffset The offset to the particular node.
 * @name: name of the prop to locate
 * @array_addr: The value part of the specified element will be read into
 * @array_size: how many members in this array.
 * @index: which array to read, start from 0
 *
 * nvdt_read_array_by_index used to get the value like
 * local-loopbacks = <0 1>, <5 6>;
 *
 * returns:
 *    NO_ERROR , on success
 *    -FDT_ERR_NOTFOUND, if the requested nodeoffset does not exist
 *    -FDT_ERR_BADOFFSET, if the requested index does not exist
 */
int nvdt_read_array_by_index(const void *nvdt, int nodeoffset, const char *name,
        uint32_t *array_addr, uint32_t array_size, uint32_t index);

/**
 * nvdt_read_clock_info_by_name - get the clock info for a given node
 *  for a given name.
 * @nvdt: pointer to the device tree blob
 * @nodeoffset The offset to the particular node.
 * @clk_name: name of the clock
 * @phandle: Pointer to hold the phandle associated with the clock
 * @clk_id: Pointer to hold the clk_id associated with the clock
 *
 * returns:
 *    0 , on success and returns phandle/clk_id in the pointers
 *      passed by the caller
 *    -FDT_ERR_NOTFOUND, if the requested nodeoffset does not exist
 */
int32_t nvdt_read_clock_info_by_name(const void *fdt, int32_t nodeoffset,
    const char *clk_name, int32_t *phandle, int32_t *clk_id);

/**
 * nvdt_read_reset_info_by_name - get the reset info for a given node
 *  for a given name.
 * @nvdt: pointer to the device tree blob
 * @nodeoffset The offset to the particular node.
 * @reset_name: name of the reset
 * @phandle: Pointer to hold the phandle associated with the reset
 * @reset_id: Pointer to hold the reset_id associated with the reset
 *
 * returns:
 *    0 , on success and returns phandle/reset_id in the pointers
 *      passed by the caller
 *    -FDT_ERR_NOTFOUND, if the requested nodeoffset/name does not exist
 */
int32_t nvdt_read_reset_info_by_name(const void *fdt, int32_t nodeoffset,
    const char *reset_name, int32_t *phandle, int32_t *reset_id);

/**
 * nvdt_read_array_by_name - get the array value of a give prop name in a node.
 * @nvdt: pointer to the device tree blob
 * @nodeoffset The offset to the particular node.
 * @name: name of the prop to locate
 * @array_addr: The value part of the specified element will be read into
 * @array_size: how many members in this array.
 *
 * nvdt_read_array_by_name used to get the value like
 * peers = <2 10>;
 *
 * returns:
 *    NO_ERROR , on success
 *    -FDT_ERR_NOTFOUND, if the requested nodeoffset does not exist
 */
int nvdt_read_array_by_name(const void *nvdt, int nodeoffset, const char *name,
        uint32_t *array_addr, uint32_t array_size);

/**
 * dt_read_prop_by_name - find a prop of a given name
 * @nvdt: pointer to the device tree blob
 * @nodeoffset The offset to the particular node.
 * @name: name of the prop to locate
 * @value: The value part of the specified element will be read into
 *
 * dt_read_prop_by_name = nvdt_read_array_by_name(nodeoffset, name, value, 1);
 *
 * returns:
 *    NO_ERROR , on success
 *    -FDT_ERR_NOTFOUND, if the requested prop does not exist
 */
int nvdt_read_prop_by_name(const void *nvdt, int nodeoffset, const char *name,
        uint32_t *value);

/**
 * dt_read_reg_by_node: Read first <addr,size> tuple in "reg" property
 * of a device node specified at particular offset.
 *
 * @param nvdt pointer to the device tree blob
 * @param nodeoffset The offset to the particular node.
 * @param addr The addr part of the specified element will be read into
 *  this field. address will not be read if this is NULL.
 * @param size The size part of the specified element will be read into
 *  this field. size will not be read if this is NULL.
 *
 * @returns NO_ERROR if the specified addr and/or size is read successfully,
 *  otherwise appropriate error.
 */
int nvdt_read_reg_by_node(const void *nvdt, int nodeoffset, uintptr_t *addr,
        uintptr_t *size);

/**
 * dt_read_reg_by_index: Read an <addr,size> tuple in "reg" property
 * of a device node specified at particular offset.
 *
 * @param nvdt pointer to the device tree blob
 * @param nodeoffset The offset to the particular node.
 * @param index The index of <addr,size> tuple to be read.
 * @param addr The addr part of the specified element will be read into
 *  this field. address will not be read if this is NULL.
 * @param size The size part of the specified element will be read into
 *  this field. size will not be read if this is NULL.
 *
 * @returns NO_ERROR if the specified addr and/or size is read successfully,
 *  otherwise appropriate error.
 */
int nvdt_read_reg_by_index(const void *nvdt, int nodeoffset, uint32_t index,
        uintptr_t *addr, uintptr_t *size);

/**
 * nvdt_node_check_compatible: Check if node has a matching compatible string.
 * The compatible string can have multiple entries separated by ":".
 *
 * @param nvdt pointer to the device tree blob
 * @param nodeoffset The offset of the node to check.
 * @param compatible Compatible string to look for. It can have multiple entries
    separated by ":".
 *
 * @returns 1 if node has a matching compatible string, 0 otherwise.
 */
int nvdt_node_check_compatible(const void *nvdt, int nodeoffset,
                const char *compatible);

/**
 * nvdt_node_offset_by_compatible: Get offset of node matching the compatible
 * string. The compatible string can have multiple entries separated by ":".
 * The function will find the first node matching any of those entries.
 *
 * @param nvdt pointer to the device tree blob
 * @param startoffset The offset from where to start looking.
 * @param compatible Compatible string to look for. It can have multiple entries
    separated by ":".
 *
 * @returns Offset of the first node that matches any of the compatible strings.
 */
int nvdt_node_offset_by_compatible(const void *nvdt, int startoffset,
                const char *compatible);

/**
 * nvdt_node_offset_by_compatible_and_addr: Get offset of node matching the
 * compatible string and the address. The compatible string can have multiple
 * entries separated by ":". The function will find the first node matching any
 * of those entries and the address.
 *
 * @param nvdt pointer to the device tree blob
 * @param startoffset The offset from where to start looking.
 * @param compatible Compatible string to look for. It can have multiple entries
    separated by ":".
 * @param Physical address of the HW module to match.
 *
 * @returns Offset of the first node that matches any of the compatible strings
 *  and the address.
 */
int nvdt_node_offset_by_compatible_and_addr(const void *nvdt, int startoffset,
                const char *compatible, uint64_t addr);


/**
 * nvdt_next_child_node: Get offset of the next child node for the parent with
 * the given depth.
 *
 * Inputs:
 * @param nvdt pointer to the device tree blob
 * @param startoffset The offset from where to start looking.
 * @param parent_node_depth: Depth of the parent node, whose next child is to
 *  be found.
 *
 * Outputs:
 * @param child_node_offset: Pointer to the location where the next child offset
 *  will be stored.
 *
 * @returns:
 *  NVDT_INVALID, if the arguments are not valid..
 *  NVDT_NO_NODE, if child node cannot be found.
 *  NVDT_SUCCESS, on success.
 */
nvdt_error nvdt_next_child_node(const void *nvdt, int startoffset,
                int parent_node_depth, int *child_node_offset);

/**
 * nvdt_map_regs: Gets and maps all the base addresses in the "regs" field. It
 * creates a list of physical and virtual addresses and their sizes.
 * All the addresses will be mapped as nGnRnE kind of memory. The client must
 * call the nvdt_unmap_regs() routine to cleanly unmap the address and release
 * memory.
 *
 * @param nvdt pointer to the device tree blob
 * @param startoffset The offset from where to start looking.
 * @param reg_base Pointer to the location where pointers to lists of base
 *  addresses is saved.
 *
 * @returns
 *  NVDT_NO_PROP, if "reg" property is not found.
 *  NVDT_INVALID, if the arguments or data in DT is invalid.
 *  NVDT_SUCCESS, on success.
 *  NVDT_ERROR, on other errors.
 */
nvdt_error nvdt_map_regs(const void *nvdt, int startoffset,
    struct nvdt_base **reg_base);

/**
 * nvdt_map_regs: Unmaps all the base addresses mapped by nvdt_map_regs().
 *
 * @param reg_base Pointer to the list returned by nvdt_map_regs().
 */
void nvdt_unmap_regs(struct nvdt_base **reg_base);

/**
 * It takes error number as an nvdt_error enum.
 * and returns string that contains error msg.
 */
const char *nvdt_error_string(nvdt_error err_num);

/*******************************************************************
 * The following APIs are just wrapper around the base DT functions
 ******************************************************************/

const void *nvdt_offset_ptr(const void *nvdt, int offset, unsigned int checklen);
uint32_t nvdt_next_tag(const void *nvdt, int offset, int *nextoffset);
int nvdt_next_node(const void *nvdt, int offset, int *depth);
int nvdt_check_header(const void *nvdt);
const char *nvdt_string(const void *nvdt, int stroffset);
int nvdt_num_mem_rsv(const void *nvdt);
int nvdt_get_mem_rsv(const void *nvdt, int n, uint64_t *address, uint64_t *size);
int nvdt_subnode_offset_namelen(const void *nvdt, int parentoffset,
                const char *name, int namelen);
int nvdt_subnode_offset(const void *nvdt, int parentoffset, const char *name);
int nvdt_path_offset(const void *nvdt, const char *path);
const char *nvdt_get_name(const void *nvdt, int nodeoffset, int *lenp);
int nvdt_first_property_offset(const void *nvdt, int nodeoffset);
int nvdt_next_property_offset(const void *nvdt, int offset);
const struct nvdt_property *nvdt_get_property_by_offset(const void *nvdt,
                int offset, int *lenp);
const struct nvdt_property *nvdt_get_property_namelen(const void *nvdt,
                int nodeoffset, const char *name, int namelen, int *lenp);
const struct nvdt_property *nvdt_get_property(const void *nvdt, int nodeoffset,
                const char *name, int *lenp);
const void *nvdt_getprop_by_offset(const void *nvdt, int offset,
                const char **namep, int *lenp);
const void *nvdt_getprop_namelen(const void *nvdt, int nodeoffset,
                const char *name, int namelen, int *lenp);
const void *nvdt_getprop(const void *nvdt, int nodeoffset,
                const char *name, int *lenp);
uint32_t nvdt_get_phandle(const void *nvdt, int nodeoffset);
const char *nvdt_get_alias_namelen(const void *nvdt,
                const char *name, int namelen);
const char *nvdt_get_alias(const void *nvdt, const char *name);
int nvdt_get_path(const void *nvdt, int nodeoffset, char *buf, int buflen);
int nvdt_supernode_atdepth_offset(const void *nvdt, int nodeoffset,
                int supernodedepth, int *nodedepth);
int nvdt_node_depth(const void *nvdt, int nodeoffset);
int nvdt_parent_offset(const void *nvdt, int nodeoffset);
int nvdt_node_offset_by_prop_value(const void *nvdt, int startoffset,
                const char *propname, const void *propval, int proplen);
int nvdt_node_offset_by_phandle(const void *nvdt, uint32_t phandle);

/*****************************************************************
 * API FOR TEGRA PROD SETTINGS
 *****************************************************************/

/**
 * Get the complete prod settings list.
 *
 * Inputs:
 *  @nvdt: DT pointer.
 *  @nvdt_node_offset: Node offset in the FDT.
 *
 * Outputs:
 *  @tegra_prod_list: Pointer to the list. The value pointed by this arg will
 *    be allocated the memory for the list.
 *
 * Returns:
 *  NVDT_NO_NODE, if there is no "prod-settings" node OR if it is disabled
 *      OR the node has no subnodes OR no valid subnode is found.
 *  NVDT_INVALID, if the arguments are invalid.
 *  NVDT_SUCCESS, on success.
 *  NVDT_ERROR, for all other errors.
 */
nvdt_error nvdt_prod_get_list(const void *nvdt, int nvdt_node_offset,
    struct nv_tegra_prod_list **tegra_prod_list);

/**
 * Get the prod settings list by name of prod settings.
 *
 * Inputs:
 *  @nvdt: DT pointer.
 *  @nvdt_node_offset: Node offset in the FDT.
 *  @name: Name of prod-settings.
 *
 * Outputs:
 *  @tegra_prod_list: Pointer to the list. The value pointed by this arg will
 *    be allocated the memory for the list.
 *
 * Returns:
 *  NVDT_NO_NODE, if there is no "prod-settings" node OR if it is disabled
 *      OR the node has no subnodes OR no valid subnode is found.
 *  NVDT_INVALID, if the arguments are invalid.
 *  NVDT_SUCCESS, on success.
 *  NVDT_ERROR, for all other errors.
 */
nvdt_error nvdt_prod_get_by_name(const void *nvdt, int nvdt_node_offset, const char *name,
    struct nv_tegra_prod_list **tegra_prod_list);


/**
 * Set all the tuples for all prod settings.
 *
 * Inputs:
 * @vbase: Array of virtual bases.
 *     The address in the tuples will be added to this base.
 * @num_vbase: Number of base addresses in the array.
 * @tegra_prod_list: Prod settings list.
 *
 * Returns:
 *    NVDT_INVALID: If arguments are invalid.
 *    NVDT_SUCCESS: On Success.
 */
nvdt_error nvdt_prod_set_list(uintptr_t *vbase, uint32_t num_vbase,
                struct nv_tegra_prod_list *tegra_prod_list);

/**
 * Set all the tuples for all prod settings with property
 * "nvidia,prod-boot-init".
 *
 * Inputs:
 * @vbase: Array of virtual bases.
 *     The address in the tuples will be added to this base.
 * @num_vbase: Number of base addresses in the array.
 * @tegra_prod_list: Prod settings list.
 *
 * Returns:
 *    NVDT_INVALID: If arguments are invalid.
 *    NVDT_SUCCESS: On Success.
 */
nvdt_error nvdt_prod_set_boot_init(uintptr_t *vbase, uint32_t num_vbase,
                struct nv_tegra_prod_list *tegra_prod_list);

/**
 * Set all the tuples for all prod settings with a given name.
 *
 * Inputs:
 * @vbase: Array of virtual bases.
 *     The address in the tuples will be added to this base.
 * @num_vbase: Number of base addresses in the array.
 * @name: Name of the prod setting to set.
 * @tegra_prod_list: Prod settings list.
 *
 * Returns:
 *    NVDT_INVALID: If arguments are invalid.
 *    NVDT_SUCCESS: On Success.
 */
nvdt_error nvdt_prod_set_by_name(uintptr_t *vbase, uint32_t num_vbase,
                const char *name, struct nv_tegra_prod_list *tegra_prod_list);

/**
 * nvdt_prod_set_by_name_partially - Set the prod setting from list partially
 * under given prod name. The matching is done with index, offset and mask.
 *
 * Inputs
 * @vbase           : Array of virtual bases.
 *                    The address in the tuples will be added to this base.
 * @num_vbase       : Number of base addresses in the array.
 * @name            : The name of tegra prod need to set.
 * @tegra_prod_list : Prod settings list.
 * @index           : Index of base address.
 * @offset          : Offset of the register.
 * @mask            : Mask field on given register.
 *
 * Find the tegra prod in the list according to the name. Then set
 * that tegra prod which has matching of index, offset and mask.
 *
 * Returns:
 *    NVDT_INVALID: If arguments are invalid.
 *    NVDT_SUCCESS: On Success.
 */

nvdt_error nvdt_prod_set_by_name_partially(uintptr_t *vbase, uint32_t num_vbase,
            const char *name, struct nv_tegra_prod_list *tegra_prod_list,
            uint32_t index, uint32_t offset, uint32_t mask);

/**
 * Releases all the memory used by the prod settings list.
 *
 * Inputs:
 * @tegra_prod_list: Pointer to the prod settings list.
 *
 * Returns:
 *    NVDT_SUCCESS: On Success
 */
nvdt_error nvdt_prod_release(struct nv_tegra_prod_list **tegra_prod_list);


/*****************************************************************
 * SOME COMMONLY USED FUNCTIONS WITH DT
 *****************************************************************/
uint32_t nv_be_u32(uint32_t val);

/*****************************************************************
 * SOME COMMONLY USED MACROS
 *****************************************************************/

/**
 * Find the node by it's name
 * Arguments:-
 * 1. nvdt: DTB handle.
 * 2. name: Name of node to find in DT.
 * 3. start_offset: Start searching for node from this offset.
 * 4. node_offset: It is a output, Return the offset of desired node.
 * 5. err_str: Node name which can be used in case of error.
 */
#define FIND_NODE_BY_NAME(nvdt, name, start_offset, node_offset, err_str) \
    do { \
        err_str = name;                                                        \
        node_offset = nvdt_subnode_offset(nvdt, start_offset, name);           \
        if (node_offset < 0) {                                                 \
            status = NVDT_NO_NODE;                                             \
            goto fail;                                                         \
        }                                                                      \
    } while(0);

#define CHECK_NODE_STATUS(nvdt, node_offset) \
    do { \
        if (nvdt_is_status_okay(nvdt, node_offset) == 0) {                     \
            status = NVDT_DISABLED;                                            \
            goto fail;                                                         \
        }                                                                      \
    } while(0);

#define FIND_NODE_BY_NAME_AND_CHECK_STATUS(nvdt, name, start_offset, node_offset, err_str) \
    do { \
        FIND_NODE_BY_NAME(nvdt, name, start_offset, node_offset, err_str)       \
        CHECK_NODE_STATUS(nvdt, node_offset)                                    \
    } while(0);

#define FIND_NODE_BY_COMPATIBLE_STRING(nvdt, string,                            \
        start_offset, node_offset, err_str)                                    \
    do { \
        err_str = string;                                                      \
        node_offset = nvdt_node_offset_by_compatible(nvdt, start_offset, string); \
        if (node_offset < 0) {                                                 \
            status = NVDT_NO_NODE;                                             \
            goto fail;                                                         \
        }                                                                      \
    } while (0);

#define FIND_NODE_BY_COMPATIBLE_STRING_AND_CHECK_STATUS(nvdt, string,           \
        start_offset, node_offset, err_str)                                    \
    do { \
        err_str = string;                                                      \
        FIND_NODE_BY_COMPATIBLE_STRING(nvdt, string, start_offset, node_offset, \
            err_str)                                                           \
        CHECK_NODE_STATUS(nvdt, node_offset)                                    \
    } while(0);

/**
 * Find the node by it's compatible string and controller address.
 * Arguments:-
 * 1. nvdt: DTB handle.
 * 2. name: Compatible of node to find in DT.
 * 3. addr: addr of controller.
 * 4. start_offset: Start searching for node from this offset.
 * 5. node_offset: It is a output, Return the offset of desired node.
 * 6. err_str: Node name which can be used in case of error.
 */
#define FIND_NODE_BY_COMPATIBLE_STRING_AND_ADDR_WITH_CHECK_STATUS(nvdt, string, \
        addr, start_offset, node_offset, err_str)                              \
    do { \
        err_str = string;                                                        \
        node_offset = nvdt_node_offset_by_compatible_and_addr(nvdt, start_offset, \
            string, addr);                                                       \
        if (node_offset < 0) {                                                 \
            status = NVDT_NO_NODE;                                             \
            goto fail;                                                         \
        }                                                                      \
        CHECK_NODE_STATUS(nvdt, node_offset)                                   \
    } while(0);

/**
 * Find next node from this offset
 * Arguments:-
 * 1. nvdt: DTB handle.
 * 2. offset: start offset from where next node will be searched
 * Output:-
 * offset of next node will be stored in "offset".
 */
#define FIND_NEXT_NODE(nvdt, offset) \
    do { \
        offset = nvdt_next_node(nvdt, offset, NULL);            \
        if (offset < 0) {                                       \
            status = NVDT_NO_NEXT_NODE;                         \
            goto fail;                                          \
        }                                                       \
    } while (0);

/**
 * Find next node from this offset
 * Arguments:-
 * 1. nvdt: DTB handle.
 * 2. offset: start offset from where next node will be searched
 * Output:-
 * offset of next node will be stored in "offset".
 */
#define FIND_NEXT_NODE_AND_CHECK_STATUS(nvdt, offset) \
    do { \
        FIND_NEXT_NODE(nvdt, offset)                            \
        CHECK_NODE_STATUS(nvdt, offset)                         \
        }                                                       \
    } while (0);

/**
 * Get the property by name
 * 1. nvdt: DTB handle.
 * 2. offset: start offset from where property is searched.
 * 3. name: name of property.
 * 4. prop_len: It is a output, length of property will be stored in it.
 *              property length is the number of bytes in that property.
 * 5. prop_count: minimum expected number of property.
                  property should have minimum "prop_count" elements.
                  If property has string as value then 0 should be passed.
 * 6. prop: It is a output, start offset of property value.
 * 7. err_str: Property name which can be used in case of error.
 */
#define GET_PROP(nvdt, offset, name, prop_len, prop_count, prop, err_str)  \
    do { \
        err_str = name;                                          \
        prop = nvdt_getprop(nvdt, offset, name, &prop_len);      \
        if (!prop) {                                             \
            status = NVDT_NO_PROP;                               \
            goto fail;                                           \
        }                                                        \
        if (prop_len < (int) (prop_count * sizeof(uint32_t))) {  \
            status = NVDT_INVALID;                               \
            goto fail;                                           \
        }                                                        \
    } while (0);

/* Validate the string which should be non-empty */
#define VALIDATE_STRING_PROPERTY(prop)   \
    do { \
        if (!prop || !strlen(prop) ) {   \
            status = NVDT_NULL_PTR;      \
            goto fail;                   \
        }                                \
    } while(0);

#endif // __NVDTCOMMON_H
