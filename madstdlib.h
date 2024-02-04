#ifndef MADSTDLIB_H
#define MADSTDLIB_H

#define MADERROR unsigned int

#define MAD_ERROR_UNKNOW_ERR -1
#define MAD_ERROR_OK 0
#define MAD_ERROR_INVALID_PAR 1
#define MAD_ERROR_SURPLUS_CALL 2
#define MAD_ERROR_INVALID_CALL 3
#define MAD_ERROR_UNFINISHED_FUNCTION 4
#define MAD_ERROR_MEMORY_OVERFLOW 5
#define MAD_ERROR_MEMORY_LACK 6
#define MAD_ERROR_MEMORY_MISSING 7

struct MADVersion {
	unsigned int MajorVersion;
	unsigned int MinorVersion;
	unsigned int RevisionVersion;
	unsigned int BuildVersion;
	MADVersion() {
		MajorVersion = 0;
		MinorVersion = 0;
		RevisionVersion = 0;
		BuildVersion = 0;
	}
	MADVersion(const unsigned int _MajorVersion, const unsigned int _MinorVersion,
			const unsigned int _RevisionVersion, const unsigned int _BuildVersion = 0) {
		MajorVersion = _MajorVersion;
		MinorVersion = _MinorVersion;
		RevisionVersion = _RevisionVersion;
		BuildVersion = _BuildVersion;
	}
	MADVersion(const MADVersion &_MADVersion) {
		MajorVersion = _MADVersion.MajorVersion;
		MinorVersion = _MADVersion.MinorVersion;
		RevisionVersion = _MADVersion.RevisionVersion;
		BuildVersion = _MADVersion.BuildVersion;
	}
	bool operator==(const MADVersion &_MADVersion) const {
		return (MajorVersion == _MADVersion.MajorVersion &&
				MinorVersion == _MADVersion.MinorVersion &&
				RevisionVersion == _MADVersion.RevisionVersion &&
				BuildVersion == _MADVersion.BuildVersion);
	}
	bool operator<(const MADVersion &_MADVersion) const {
		if (MajorVersion == _MADVersion.MajorVersion) {
			if (MinorVersion == _MADVersion.MinorVersion) {
				if (RevisionVersion == _MADVersion.RevisionVersion) {
					if (BuildVersion == _MADVersion.BuildVersion) {
						return false;
					}
					if (BuildVersion < _MADVersion.BuildVersion) {
						return true;
					} else {
						return false;
					}
				}
				if (RevisionVersion < _MADVersion.RevisionVersion) {
					return true;
				} else {
					return false;
				}
			}
			if (MinorVersion < _MADVersion.MinorVersion) {
				return true;
			} else {
				return false;
			}
		}
		if (MajorVersion < _MADVersion.MajorVersion) {
			return true;
		} else {
			return false;
		}
	}
	bool operator>(const MADVersion &_MADVersion) const {
		if (MajorVersion == _MADVersion.MajorVersion) {
			if (MinorVersion == _MADVersion.MinorVersion) {
				if (RevisionVersion == _MADVersion.RevisionVersion) {
					if (BuildVersion == _MADVersion.BuildVersion) {
						return false;
					}
					if (BuildVersion > _MADVersion.BuildVersion) {
						return true;
					} else {
						return false;
					}
				}
				if (RevisionVersion > _MADVersion.RevisionVersion) {
					return true;
				} else {
					return false;
				}
			}
			if (MinorVersion > _MADVersion.MinorVersion) {
				return true;
			} else {
				return false;
			}
		}
		if (MajorVersion > _MADVersion.MajorVersion) {
			return true;
		} else {
			return false;
		}
	}
	bool operator<=(const MADVersion &_MADVersion) const {
		if (MajorVersion == _MADVersion.MajorVersion) {
			if (MinorVersion == _MADVersion.MinorVersion) {
				if (RevisionVersion == _MADVersion.RevisionVersion) {
					if (BuildVersion == _MADVersion.BuildVersion) {
						return true;
					}
					if (BuildVersion < _MADVersion.BuildVersion) {
						return true;
					} else {
						return false;
					}
				}
				if (RevisionVersion < _MADVersion.RevisionVersion) {
					return true;
				} else {
					return false;
				}
			}
			if (MinorVersion < _MADVersion.MinorVersion) {
				return true;
			} else {
				return false;
			}
		}
		if (MajorVersion < _MADVersion.MajorVersion) {
			return true;
		} else {
			return false;
		}
	}
	bool operator>=(const MADVersion &_MADVersion) const {
		if (MajorVersion == _MADVersion.MajorVersion) {
			if (MinorVersion == _MADVersion.MinorVersion) {
				if (RevisionVersion == _MADVersion.RevisionVersion) {
					if (BuildVersion == _MADVersion.BuildVersion) {
						return true;
					}
					if (BuildVersion > _MADVersion.BuildVersion) {
						return true;
					} else {
						return false;
					}
				}
				if (RevisionVersion > _MADVersion.RevisionVersion) {
					return true;
				} else {
					return false;
				}
			}
			if (MinorVersion > _MADVersion.MinorVersion) {
				return true;
			} else {
				return false;
			}
		}
		if (MajorVersion > _MADVersion.MajorVersion) {
			return true;
		} else {
			return false;
		}
	}
};

#define MAD_VER_TO_STR(ver) itos(ver.MajorVersion) + "." + itos(ver.MinorVersion) + "." + itos(ver.RevisionVersion) + "." + itos(ver.BuildVersion)












#endif
