#include "languagemanager.h"

#include <QApplication>
#include <QDir>
#include <QLibraryInfo>
#include <QMessageBox>
#include <QTranslator>

LanguageManager &LanguageManager::instance() {
    static LanguageManager ins;
    return ins;
}

LanguageManager::LanguageManager() {
    auto langPath =
        qApp->applicationDirPath() + QDir::separator() + QStringLiteral("lang");

    QDir langDir(langPath);
    Q_ASSERT(langDir.exists());

    auto langFiles = langDir.entryInfoList(QDir::Files);
    for (auto &langinfo : langFiles) {
        auto lang = langinfo.baseName();
        if (!lang.startsWith(APP_NAME)) {
            continue;
        }
        lang = lang.mid(strlen(APP_NAME) + 1);
        QLocale locale(lang);
        if (locale == QLocale::C) {
            continue;
        }
        m_langs << lang;
        m_localeMap.insert(lang, locale);
    }

    _defaultLocale = QLocale::system();

    if (m_langs.isEmpty()) {
#if QT_VERSION > QT_VERSION_CHECK(6, 0, 0)
        if (QLocale::China == _defaultLocale.territory()
#else
        if (QLocale::China == _defaultLocale.country()
#endif
        ) {
            QMessageBox::critical(
                nullptr, QStringLiteral("程序损坏"),
                QStringLiteral(
                    "语言文件已损坏，请尝试重装软件以解决这个问题。"));
        } else {
            QMessageBox::critical(
                nullptr, QStringLiteral("Corruption"),
                QStringLiteral("The language file has been damaged. "
                               "Please try reinstalling the software to "
                               "solve the problem."));
        }
        qApp->exit(-1);
    }

    bool found = false;
    for (auto p = m_localeMap.begin(); p != m_localeMap.end(); ++p) {
#if QT_VERSION > QT_VERSION_CHECK(6, 0, 0)
        if (p->territory() == _defaultLocale.territory() &&
#else
        if (p->country() == _defaultLocale.country() &&
#endif
            p->language() == _defaultLocale.language() &&
            p->script() == _defaultLocale.script()) {
            found = true;
            break;
        }
    }
    if (!found) {
        _defaultLocale =
            m_langs.isEmpty() ? QLocale() : m_localeMap.value(m_langs.first());
    }

    auto qtPath =
#if QT_VERSION > QT_VERSION_CHECK(6, 0, 0)
        QLibraryInfo::path(QLibraryInfo::TranslationsPath);
#else
        QLibraryInfo::location(QLibraryInfo::TranslationsPath);
#endif

    auto qtTranslator = new QTranslator(this);
    if (qtTranslator->load(_defaultLocale, QStringLiteral("qtbase"),
                           QStringLiteral("_"), qtPath)) {

        qApp->installTranslator(qtTranslator);
    }

    qtTranslator = new QTranslator(this);
    if (qtTranslator->load(_defaultLocale, QStringLiteral("qt"),
                           QStringLiteral("_"), qtPath)) {

        qApp->installTranslator(qtTranslator);
    }

    auto translator = new QTranslator(this);
    if (translator->load(_defaultLocale, QStringLiteral(APP_NAME),
                         QStringLiteral("_"),
                         qApp->applicationDirPath() + QDir::separator() +
                             QStringLiteral("lang"))) {
        qApp->installTranslator(translator);
    }

    m_langMap = {{"zh_CN", tr("Chinese(Simplified)")}};

    for (auto &lang : m_langs) {
        m_langsDisplay << m_langMap.value(lang, lang);
    }
}

QLocale LanguageManager::defaultLocale() const { return _defaultLocale; }

QStringList LanguageManager::langsDisplay() const { return m_langsDisplay; }
