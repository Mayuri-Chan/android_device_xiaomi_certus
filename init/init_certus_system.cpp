/*
 * Copyright (C) 2021 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>
#include <string>

#include "init_certus.h"

void property_override(const std::string &key, const std::string &value) {
	auto pi = (prop_info *) __system_property_find(key.c_str());

	if (pi != nullptr) {
		__system_property_update(pi, value.c_str(), value.size());
	} else {
		__system_property_add(key.c_str(), key.size(), value.c_str(), value.size());
	}
}

void vendor_load_properties() {
	properties props;

	if (get_properties(props)) {
		const auto build_fingerprint = props.fingerprint;
		const auto build_description = props.description;
		const auto build_security_patch_date = props.build_security_patch_date;
		const auto build_tags = props.build_tags;
		const auto build_type = props.build_type;
		const auto build_version_release = props.build_version_release;
		const auto product_name = props.codename;
		const auto product_model = props.model;

		for (const auto &prop : {
			"ro.bootimage.build.fingerprint",
			"ro.build.fingerprint",
			"ro.odm.build.fingerprint",
			"ro.product.build.fingerprint",
			"ro.system.build.fingerprint",
			"ro.system_ext.build.fingerprint",
			"ro.vendor.build.fingerprint",
			"ro.vendor_dlkm.build.fingerprint",
		}) {
			property_override(prop, build_fingerprint->second.c_str());
		}

		for (const auto &prop : {
			"ro.build.tags",
			"ro.odm.build.tags",
			"ro.product.build.tags",
			"ro.system.build.tags",
			"ro.system_ext.build.tags",
			"ro.vendor.build.tags",
			"ro.vendor_dlkm.build.tags",
		}) {
			property_override(prop, build_tags->second.c_str());
		}

		for (const auto &prop : {
			"ro.build.type",
			"ro.odm.build.type",
			"ro.product.build.type",
			"ro.system.build.type",
			"ro.system_ext.build.type",
			"ro.vendor.build.type",
			"ro.vendor_dlkm.build.type",
		}) {
			property_override(prop, build_type->second.c_str());
		}

		for (const auto &prop : {
			"ro.build.version.release",
			"ro.odm.build.version.release",
			"ro.product.build.version.release",
			"ro.system.build.version.release",
			"ro.system_ext.build.version.release",
			"ro.vendor.build.version.release",
			"ro.build.version.release_or_codename",
			"ro.odm.build.version.release_or_codename",
			"ro.product.build.version.release_or_codename",
			"ro.system.build.version.release_or_codename",
			"ro.system_ext.build.version.release_or_codename",
			"ro.vendor.build.version.release_or_codename",
			"ro.vendor_dlkm.build.version.release_or_codename",
		}) {
			property_override(prop, build_version_release->second.c_str());
		}

		for (const auto &prop : {
			"ro.product.name",
			"ro.product.odm.name",
			"ro.product.product.name",
			"ro.product.system.name",
			"ro.product.system_ext.name",
			"ro.product.vendor.name",
			"ro.product.vendor_dlkm.name",
		}) {
			property_override(prop, product_name->second.c_str());
		}

		for (auto &prop : {
			"ro.product.model",
			"ro.product.odm.model",
			"ro.product.product.model",
			"ro.product.system.model",
			"ro.product.system_ext.model",
			"ro.product.vendor.model",
			"ro.product.vendor_dlkm.model",
		}) {
			property_override(prop, product_model->second.c_str());
		}

		property_override("ro.build.description", build_description->second.c_str());
		property_override("ro.build.version.security_patch", build_security_patch_date->second.c_str());
		property_override("ro.secure", "0");
		property_override("ro.adb.secure", "0");
		property_override("ro.debuggable", "0");
		property_override("ro.boot.flash.locked", "1");
		property_override("ro.boot.vbmeta.device_state", "locked");
		property_override("ro.boot.verifiedbootstate", "green");
		property_override("ro.boot.veritymode", "enforcing");
		property_override("ro.boot.warranty_bit", "0");
		property_override("ro.warranty_bit", "0");
		property_override("ro.control_privapp_permissions", "log");
	}
}
