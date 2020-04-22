/*
 * libekmfweb - EKMFWeb client library
 *
 * Copyright IBM Corp. 2020
 *
 * s390-tools is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */

#ifndef UTILITIES_H
#define UTILITIES_H

#include <stddef.h>
#include <stdbool.h>

#include <openssl/x509.h>
#include <openssl/obj_mac.h>
#include <openssl/evp.h>

#include <json-c/json.h>

#include "ekmfweb/ekmfweb.h"

int decode_base64url(unsigned char *output, size_t *outlen,
		     const char *input, size_t inlen);

int encode_base64url(char *output, size_t *outlen,
		     const unsigned char *input, size_t inlen);

int parse_json_web_token(const char *token, json_object **header_obj,
			 json_object **payload_obj, unsigned char **signature,
			 size_t *signature_len);

size_t ecc_get_curve_prime_bits(int curve_nid);
size_t ecc_get_curve_prime_length(int curve_nid);
const char *ecc_get_curve_id(int curve_nid);
bool ecc_is_prime_curve(int curve_nid);
bool ecc_is_brainpool_curve(int curve_nid);
int ecc_get_curve_by_id(const char *curve_id);
int ecc_get_prime_curve_by_prime_bits(size_t prime_bits);
int ecc_get_brainpool_curve_by_prime_bits(size_t prime_bits);

int ecc_calculate_y_coordinate(int nid, size_t prime_len,
			       const unsigned char *x, int y_bit,
			       unsigned char *y);

int ecc_pub_key_as_pkey(int nid, size_t prime_len, const unsigned char *x,
			const unsigned char *y, EVP_PKEY **pkey);

int rsa_pub_key_as_pkey(const unsigned char *modulus, size_t modulus_length,
			const unsigned char *pub_exp, size_t pub_exp_length,
			int pkey_type, EVP_PKEY **pkey);

int write_key_blob(const char *filename, unsigned char *key_blob,
		   size_t key_blob_len);

int read_key_blob(const char *filename, unsigned char *key_blob,
		  size_t *key_blob_len);

int read_x509_certificate(const char *pem_filename, X509 **cert);

int write_x509_certificate(const char *pem_filename, X509 *cert);

int write_x509_request(const char *pem_filename, X509_REQ *req, bool new_hdr);

typedef int (*rsa_sign_t)(const unsigned char *key_blob, size_t key_blob_length,
			  unsigned char *sig, size_t *siglen,
			  const unsigned char *tbs, size_t tbslen,
			  int padding_type, int md_nid,
			  void *private);
typedef int (*rsa_pss_sign_t)(const unsigned char *key_blob,
			      size_t key_blob_length, unsigned char *sig,
			      size_t *siglen, const unsigned char *tbs,
			      size_t tbslen, int md_nid, int mfgmd_nid,
			      int saltlen, void *private);
typedef int (*ecdsa_sign_t)(const unsigned char *key_blob,
			    size_t key_blob_length, unsigned char *sig,
			    size_t *siglen, const unsigned char *tbs,
			    size_t tbslen, int md_nid, void *private);

struct sk_pkey_sign_func {
	rsa_sign_t      rsa_sign;
	rsa_pss_sign_t  rsa_pss_sign;
	ecdsa_sign_t    ecdsa_sign;
};

int setup_secure_key_pkey_method(int pkey_id);
int cleanup_secure_key_pkey_method(int pkey_id);
int setup_secure_key_pkey_context(EVP_PKEY_CTX *pkey_ctx,
				  const unsigned char *key_blob,
				  size_t key_blob_len,
				  struct sk_pkey_sign_func *sign_funcs,
				  void *private);

int setup_rsa_pss_pkey_context(EVP_PKEY_CTX *pkey_ctx,
			       struct ekmf_rsa_pss_params *rsa_pss_params);

int build_subject_name(X509_NAME **name, const char *rdns[], size_t num_rdns,
		       bool utf8);

int build_certificate_extensions(X509 *cert, X509_REQ *req,
				 const char *exts[], size_t num_exts,
				 const STACK_OF(X509_EXTENSION) *addl_exts);

int generate_x509_serial_number(X509 *cert, size_t sn_bit_size);

#endif
