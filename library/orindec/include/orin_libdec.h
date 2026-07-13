/*
 * orin_libdec.h — Orin decrypt library public API
 * ============================================================
 *
 * Provides:
 *   orin_gae_dec() — full identity→handshake→ECDH→decrypt→exec flow
 *
 * Compile as static library: liborindec_orin.a
 */

#ifndef ORIN_LIBDEC_H
#define ORIN_LIBDEC_H

#include <stdint.h>

/**
 * @brief Complete Orin GAE decrypt-and-execute flow.
 *
 * Performs the full secure boot sequence:
 *   Phase 1: Read HW SN → HKDF → ECC identity key pair → load whitelist
 *   Phase 2: UDP mutual authentication handshake with RK3588 (auto-retry)
 *   Phase 3: ECDH → SessionKey
 *   Phase 4: Request ModelKey via RK, decrypt GAE.enc → memfd → fork-exec
 *
 * All transient failures (UDP timeout, signature mismatch) trigger
 * automatic retry.  Only fatal errors (missing HW SN, missing whitelist)
 * return immediately.
 *
 * @param gae_enc_path   Path to encrypted GAE file, e.g. "GAE.enc"
 * @param gae_argv       NULL-terminated argument vector for the child
 *                       process.  argv[0] is the process name (display only,
 *                       actual binary comes from decrypted memfd).
 *                       Example:  const char *argv[] = {"GAE", "cxk", NULL}
 *
 * @retval  0  Success — GAE process launched via fork-exec
 * @retval -1  Phase 1 fatal: HW SN unreachable or whitelist missing
 * @retval  1  Internal fatal (unrecoverable ECC error)
 */

#ifdef __cplusplus
extern "C" {
#endif

int orin_gae_dec(const char *gae_enc_path, const char **gae_argv);

#ifdef __cplusplus
}
#endif

#endif /* ORIN_LIBDEC_H */
