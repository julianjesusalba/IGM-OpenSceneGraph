#include <osg/Geode>
#include <osg/Material>
#include <osg/ShapeDrawable>
#include <osgViewer/Viewer>
#include <osg/MatrixTransform>
#include <osgGA/TrackballManipulator>


int main() {

    // Creamos el nodo raíz
    osg::ref_ptr<osg::Group> root = new osg::Group;

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
    osg::Vec3d eye(0, 0, 8); // Ajustamos la posición inicial de la cámara
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
