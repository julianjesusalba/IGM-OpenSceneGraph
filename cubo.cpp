#include <osg/Geode>
#include <osg/Material>
#include <osg/Texture2D>
#include <osg/ShapeDrawable>
#include <osgViewer/Viewer>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>
#include <osgGA/TrackballManipulator>
#include <osgDB/ReadFile>


int main() {

    // Creamos el nodo raíz
    osg::ref_ptr<osg::Group> root = new osg::Group;

    // Creamos la nueva fuente de luz
    osg::ref_ptr<osg::PositionAttitudeTransform> lightPAT(new osg::PositionAttitudeTransform());
    lightPAT->setPosition(osg::Vec3(0.0, 2.0, 0.0));
    root->addChild(lightPAT);

    // Setup GL_LIGHT1. Leave GL_LIGHT0 as it is by default (enabled)
    osg::ref_ptr<osg::LightSource> lightSource(new osg::LightSource());
    lightSource->addChild(new osg::ShapeDrawable(new osg::Box(osg::Vec3(), 0.4f)));
    lightSource->getLight()->setLightNum(1);
    lightSource->getLight()->setPosition(osg::Vec4(0.0, -0.4, 0.0, 1.0));
    lightSource->getLight()->setDiffuse(osg::Vec4(1.0, 0.0, 1.0, 1.0));
    lightPAT->addChild(lightSource);

    osg::ref_ptr<osg::StateSet> stateSet = root->getOrCreateStateSet();
    stateSet->setMode(GL_LIGHT1, osg::StateAttribute::ON);

    // Creamos los cubos utilizando ShapeDrawable y Box
    osg::ref_ptr<osg::ShapeDrawable> cubeDrawable = new osg::ShapeDrawable(new osg::Box(osg::Vec3(), 1.0f));
    osg::ref_ptr<osg::ShapeDrawable> cubeDrawable2 = new osg::ShapeDrawable(new osg::Box(osg::Vec3(), 1.0f));

    // Creamos un material para establecer el modo de color
    osg::ref_ptr<osg::Material> material = new osg::Material;
    material->setColorMode(osg::Material::AMBIENT_AND_DIFFUSE);
    material->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4(0.2f, 0.2f, 0.2f, 1.0f));
    material->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4(0.8f, 0.8f, 0.8f, 1.0f));

    // Aplicamos el material a los conjuntos de estado
    osg::ref_ptr<osg::StateSet> stateSetCube = cubeDrawable->getOrCreateStateSet();
    osg::ref_ptr<osg::StateSet> stateSetCube2 = cubeDrawable2->getOrCreateStateSet();
    stateSetCube->setAttributeAndModes(material, osg::StateAttribute::ON);
    stateSetCube2->setAttributeAndModes(material, osg::StateAttribute::ON);

    // Aplicamos una textura al primer cubo
    osg::ref_ptr<osg::Image> image = osgDB::readImageFile("texture.jpg");
    osg::ref_ptr<osg::Texture2D> tex(new osg::Texture2D());
    tex->setImage(image);
    stateSetCube->setTextureAttributeAndModes(0, tex);

    // Aplicamos otra textura al segundo cubo
    osg::ref_ptr<osg::Image> image2 = osgDB::readImageFile("texture2.jpg");
    osg::ref_ptr<osg::Texture2D> tex2(new osg::Texture2D());
    tex2->setImage(image2);
    stateSetCube2->setTextureAttributeAndModes(0, tex2);

    // Creamos los nodos Geode
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    osg::ref_ptr<osg::Geode> geode2 = new osg::Geode;

    // Añadimos las formas de los cubos a los nodos Geode
    geode->addDrawable(cubeDrawable);
    geode2->addDrawable(cubeDrawable2);

    // Creamos nodos MatrixTransform para rotar los cubos
    osg::ref_ptr<osg::MatrixTransform> cubeTransform = new osg::MatrixTransform;
    osg::ref_ptr<osg::MatrixTransform> cubeTransform2 = new osg::MatrixTransform;
    cubeTransform->addChild(geode);
    cubeTransform2->addChild(geode2);

    // Creamos un visor para visualizar la escena y configuramos el tamaño de la ventana
    osgViewer::Viewer viewer;
    viewer.setUpViewInWindow(200, 200, 1000, 800);

    // Añadimos los nodos MatrixTransform al nodo raíz y lo usamos como escena
    root->addChild(cubeTransform);
    root->addChild(cubeTransform2);
    viewer.setSceneData(root);

    // Establecemos el manipulador de cámara y ajustamos la distancia inicial
    osgGA::TrackballManipulator* manipulator = new osgGA::TrackballManipulator();
    osg::Vec3d eye(0, 0, 9); // Ajustamos la posición inicial de la cámara
    osg::Vec3d center(0, 0, 0); // Ajustamos el punto hacia el que mira la cámara
    osg::Vec3d up(0, 1, 0); // Ajustamos el vector de dirección "arriba" de la cámara
    manipulator->setHomePosition(eye, center, up);
    viewer.setCameraManipulator(manipulator);

    // Configuramos las rotaciones de los cubos
    float angle = 0.0f;
    while (!viewer.done()) {
        osg::Matrix rotationMatrix, rotationMatrix2, translateMatrix, translateMatrix2;

        // Rotación en el eje Y y Traslación en el eje X del primer cubo
        rotationMatrix.makeRotate(angle, osg::Vec3(0.0f, 1.0f, 0.0f));
        translateMatrix.makeTranslate(osg::Vec3(-1.0f, 0.0f, 0.0f));
        rotationMatrix = rotationMatrix * translateMatrix; 
        cubeTransform->setMatrix(rotationMatrix);
        
        // Rotación en el eje Y y Traslación en el eje X del segundo cubo
        rotationMatrix2.makeRotate(angle, osg::Vec3(0.0f, -1.0f, 0.0f));
        translateMatrix2.makeTranslate(osg::Vec3(1.0f, 0.0f, 0.0f));
        rotationMatrix2 = rotationMatrix2 * translateMatrix2; 
        cubeTransform2->setMatrix(rotationMatrix2);

        angle += 0.01f;
        viewer.frame();
    }

    return 0;
}
