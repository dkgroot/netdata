# Created by: Mahdi Mokhtari <mokhi64@gmail.com>
# $FreeBSD: head/net-mgmt/netdata/Makefile 503006 2019-05-29 20:31:21Z olgeni $

PORTNAME=	netdata
PORTVERSION=	1.15.0
DISTVERSIONPREFIX=v
CATEGORIES=	net-mgmt

MAINTAINER=	mmokhi@FreeBSD.org
COMMENT=	Scalable distributed realtime performance and health monitoring

LICENSE=	GPLv3

LIB_DEPENDS=	libuuid.so:misc/e2fsprogs-libuuid \
		libuv.so:devel/libuv \
		liblz4.so:archivers/liblz4

RUN_DEPENDS=	bash:shells/bash \
		curl:ftp/curl

USES=		autoreconf pathfix pkgconfig:both python shebangfix ssl

USE_GITHUB=	yes
GH_ACCOUNT=	firehol

SHEBANG_GLOB=	*

NETDATA_CACHE=	/var/cache/${PORTNAME}
NETDATA_LOG=	/var/log/${PORTNAME}
NETDATA_PERST=	/var/db/${PORTNAME}

USE_LDCONFIG=	yes
GNU_CONFIGURE=	yes
CPPFLAGS+=	-D_WANT_VMMETER -I${LOCALBASE}/include
LIBS+=		-L${LOCALBASE}/lib
INSTALL_TARGET=	install-strip

SUB_LIST=	NETDATA_CACHE=${NETDATA_CACHE} \
		NETDATA_LOG=${NETDATA_LOG} \
		NETDATA_PERST=${NETDATA_PERST}

PLIST_SUB=	NETDATA_CACHE=${NETDATA_CACHE} \
		NETDATA_LOG=${NETDATA_LOG} \
		NETDATA_PERST=${NETDATA_PERST}

USE_RC_SUBR=	${PORTNAME}
SUB_FILES=	${PORTNAME}.conf.sample

USERS=		netdata
GROUPS=		netdata

OPTIONS_DEFINE=	CUPS FREEIPMI
OPTIONS_SUB=	YES

CUPS_DESC=	Enable support for cups
CUPS_CONFIGURE_ENABLE=	plugin-cups
CUPS_LIB_DEPENDS=	libcups.so:print/cups

FREEIPMI_DESC=	Enable support for freeipmi
FREEIPMI_CONFIGURE_ENABLE=	plugin-freeipmi
FREEIPMI_LIB_DEPENDS=	libfreeipmi.so:sysutils/freeipmi

post-patch:
	@${REINPLACE_CMD} -e 's|%%NETDATA_CACHE%%|${NETDATA_CACHE}|g' \
	    ${PATCH_WRKSRC}/configure.ac
	@${REINPLACE_CMD} -e 's|%%NETDATA_LOG%%|${NETDATA_LOG}|g' \
	    ${PATCH_WRKSRC}/configure.ac
	@${REINPLACE_CMD} -e 's|%%NETDATA_PERST%%|${NETDATA_PERST}|g' \
	    ${PATCH_WRKSRC}/configure.ac
	@${REINPLACE_CMD} -e 's|%%ETCDIR%%|${ETCDIR}|g' \
	    ${PATCH_WRKSRC}/configure.ac

post-install:
	${MKDIR} ${STAGEDIR}${ETCDIR}
	${INSTALL_DATA} ${WRKDIR}/netdata.conf.sample ${STAGEDIR}${ETCDIR}/netdata.conf.sample
	${MKDIR} ${STAGEDIR}${NETDATA_CACHE}
	${MKDIR} ${STAGEDIR}${NETDATA_LOG}
	${MKDIR} ${STAGEDIR}${NETDATA_PERST}
	(for file in ${STAGEDIR}${LOCALBASE}/lib/${PORTNAME}/conf.d/*.conf \
			${STAGEDIR}${LOCALBASE}/lib/${PORTNAME}/conf.d/*/*.conf; do \
		${MV} $$file $$file".sample"; \
	done)

.include <bsd.port.mk>
